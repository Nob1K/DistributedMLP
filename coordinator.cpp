// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/coordinator.h"
#include "ML.hpp"
#include "gen-cpp/Compute.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

struct node {
  std::string ip,
  int port
};

class coordinatorHandler : virtual public coordinatorIf {
 public:
  int scheduling_policy;
  coordinatorHandler(int policy) {
    // Your initialization goes here
    this->scheduling_policy = policy;
  }

  double train(const std::string& dir, const int32_t rounds, const int32_t epochs, const int32_t h, const int32_t k, const double eta) {
    // Your implementation goes here
    printf("train\n");
    mlp almighty;
    almighty.init_training_random("", k, h);

  }

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
      client.check_availability()
      transport->close();
      return true;
    } 
    catch (TException& tx) {
      return false;
    }
  }

  std::vector<node> gather_online_nodes(std::vector<node> all_nodes) {
    std::vector<node> online_nodes;
    for (const auto& n : all_nodes) {
        if (test_online_node(n.ip, n.port)) {
            online_nodes.push_back(n);
        }
    }
    return online_nodes;
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

