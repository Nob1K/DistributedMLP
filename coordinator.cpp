#include "gen-cpp/coordinator.h"
#include "ML.hpp"
#include "gen-cpp/Compute.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

namespace fs = std::filesystem;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

// global for shared gradient and file_queue, mutex locks for them
weights shared_gradient;
std::queue<std::string> file_queue;
std::mutex gradient_mutex;
std::mutex files_mutex;
std::condition_variable file_cv;
std::atomic<bool> done_training(false);
std::atomic<int> files_processed(0);
std::atomic<int> total_files(0);
std::condition_variable round_complete_cv;
std::mutex round_mutex;
bool round_complete = false;

struct node {
  std::string ip;
  int port;
};

class coordinatorHandler : virtual public coordinatorIf {
 public:
  // 1 is random, 2 is load-balancing
  int scheduling_policy;

  coordinatorHandler(int policy) {
    this->scheduling_policy = policy;
  }

  double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) {
    printf("train\n");
    mlp almighty;
    std::string validation_file = findValidationFile(dir);
    // if (!validation_file){
    //   std::cout << "couldn't find valitaion file in directory\n";
    //   return 1;
    // }
    // populate training file names
    {
      std::lock_guard<std::mutex> lock(files_mutex);
      file_queue = findTrainingFiles(dir);
    }
    // init almighty
    almighty.init_training_random(file_queue.front(), k, h);
    // clear out before re-adding during training
    {
      std::lock_guard<std::mutex> lock(files_mutex);
      while (!file_queue.empty()) file_queue.pop();
    }
    // initialize shared gradient
    gradient_mutex.lock();
    almighty.get_weights(shared_gradient.v, shared_gradient.w);
    gradient_mutex.unlock();

    // acquire online nodes
    std::vector<node> online_nodes = gather_online_nodes(extract_nodes_info("../compute_nodes.txt"));
    // spawn threads for each online node to work through training files
    vector<std::thread> threads;
    for (const auto& n : online_nodes) {
      threads.push_back(std::thread(&coordinatorHandler::thread_func, this, n, std::ref(almighty), eta, epochs));
    }
    // for loop to start rounds of training
    for (int i=0; i < rounds; i++) {
      // zero out shared gradient
      {
        std::lock_guard<std::mutex> lock(gradient_mutex);
        scale_matricies(shared_gradient.v, 0);
        scale_matricies(shared_gradient.w, 0);
      }

      // populate queue of training files then notify threads
      {
        std::lock_guard<std::mutex> lock(files_mutex);
        file_queue = findTrainingFiles(dir);
        total_files.store(file_queue.size());
        round_complete = false;
      }
      file_cv.notify_all();

      // wait for queue to be done
      {
        std::unique_lock<std::mutex> lock(round_mutex);
        round_complete_cv.wait(lock, [&] {
          return round_complete;
        });
      }
      // aggregate results
      {
        // divide gradient by total training files
        std::lock_guard<std::mutex> lock(gradient_mutex);
        scale_matricies(shared_gradient.v, 1.0 / total_files.load());
        scale_matricies(shared_gradient.w, 1.0 / total_files.load());
        // update weights of almighty
        weights current;
        almighty.get_weights(current.v, current.w);
        sum_matricies(current.v, shared_gradient.v);
        sum_matricies(current.w, shared_gradient.w);
        almighty.set_weights(current.v, current.w);
      }
      // print validate error on current round
      files_processed.store(0);
      std::cout << "round " << i+1 << " validation error: " << almighty.validate(validation_file) << std::endl;
    }
    done_training.store(true);
    file_cv.notify_all();
    // join threads
    for (auto& t : threads) {
      if (t.joinable()) {
        t.join();
      }
    }
    // return validation error
    return almighty.validate(validation_file);
  }

  // thread execution
  void thread_func(node n, mlp& model, double eta, int32_t epochs) {
    std::string training_file;
    while (true) {
      {
        // wait for files to be populated or training is completely done
        std::unique_lock<std::mutex> lock(files_mutex);
        file_cv.wait(lock, [&] {
          return !file_queue.empty() || done_training.load();
        });
        // exits thread if training is done
        if (done_training.load() && file_queue.empty()) {
          break;
        }
        // acquire file
        if (!file_queue.empty()) {
          training_file = file_queue.front();
          file_queue.pop();
        } else {
          continue;
        }
      }
      // actually contact a node
      std::shared_ptr<TTransport> socket(new TSocket(n.ip, n.port));
      std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      ComputeClient client(protocol);
      transport->open();
      bool node_available = client.check_availability();
      if (node_available) {
        weights returned_gradient;
        weights input_weights;
        model.get_weights(input_weights.v, input_weights.w);
        client.train_model(returned_gradient, input_weights, training_file, eta, epochs, false);
        // update shared gradient
        {
          std::lock_guard<std::mutex> lock(gradient_mutex);
          sum_matricies(shared_gradient.v, returned_gradient.v);
          sum_matricies(shared_gradient.w, returned_gradient.w);
          files_processed.fetch_add(1);
        }
      } 
      // load injection in random scheduling
      else if (!node_available && this->scheduling_policy == 1) {
        weights returned_gradient;
        weights input_weights;
        model.get_weights(input_weights.v, input_weights.w);
        client.train_model(returned_gradient, input_weights, training_file, eta, epochs, true);
        {
          std::lock_guard<std::mutex> lock(gradient_mutex);
          sum_matricies(shared_gradient.v, returned_gradient.v);
          sum_matricies(shared_gradient.w, returned_gradient.w);
          files_processed.fetch_add(1);
        }
      } 
      // rejected in load-balancing
      else if (!node_available && this->scheduling_policy == 2) {
        {
          std::unique_lock<std::mutex> lock(files_mutex);
          file_queue.push(training_file);
        }
        // not sure if notify is needed
        file_cv.notify_one();
      }
      transport->close();

      int processed = files_processed.load();
      // all files from current round is done, notify main thread
      if (processed == total_files.load()) {
        {
          std::lock_guard<std::mutex> lock(round_mutex);
          round_complete = true;
        }
        round_complete_cv.notify_one();
      }
    }
  }

  // extract nodes from compute_nodes.txt
  std::vector<node> extract_nodes_info(const std::string& filename) {
    std::vector<node> nodes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return nodes;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        node n;
        std::getline(ss, n.ip, ',');
        ss >> n.port;
        nodes.push_back(n);
    }

    file.close();
    return nodes;
  }

  // return true if node online, false if not
  bool test_online_node(std::string ip, int port) {
    std::shared_ptr<TTransport> socket(new TSocket(ip, port));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    ComputeClient client(protocol);
  
    try {
      transport->open();
      client.check_availability();
      transport->close();
      return true;
    } 
    catch (TException& tx) {
      return false;
    }
  }

  // return online nodes from all_nodes
  std::vector<node> gather_online_nodes(std::vector<node> all_nodes) {
    std::vector<node> online_nodes;
    for (const auto& n : all_nodes) {
        if (test_online_node(n.ip, n.port)) {
            online_nodes.push_back(n);
        }
    }
    return online_nodes;
  }

  // populate training file queue
  std::queue<std::string> findTrainingFiles(const std::string& directory) {
    std::queue<std::string> matchingFiles;
    fs::path basePath = fs::absolute(directory);

    for (const auto& entry : fs::directory_iterator(basePath)) {
        if (entry.is_regular_file()) {
            std::string fullPath = entry.path().string();
            if (fullPath.find("train") != std::string::npos) {
                matchingFiles.push(fullPath);
            }
        }
    }
    return matchingFiles;
  }

  // finds the validation file in the directory
  std::string findValidationFile(const std::string& directory) {
    std::string validation_file;
    fs::path basePath = fs::absolute(directory);

    for (const auto& entry : fs::directory_iterator(basePath)) {
        if (entry.is_regular_file()) {
            std::string fullPath = entry.path().string();
            if (fullPath.find("validate") != std::string::npos) {
                return fullPath;
            }
        }
    }
    return "";
  }
};

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: ./coordinator <port> <scheduling_policy>" << std::endl;
    return 1;
  }
    
  int port = std::stoi(argv[1]);
  int scheduling_policy = std::stoi(argv[2]);
    
  if (scheduling_policy != 1 && scheduling_policy != 2) {
    std::cerr << "Invalid scheduling policy. Use 1 for random or 2 for load-balancing." << std::endl;
    return 1;
  }

  ::std::shared_ptr<coordinatorHandler> handler(new coordinatorHandler(scheduling_policy));
  ::std::shared_ptr<TProcessor> processor(new coordinatorProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
