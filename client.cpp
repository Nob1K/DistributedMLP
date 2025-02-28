/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

 #include <iostream>
 #include <string>
 #include <thrift/protocol/TBinaryProtocol.h>
 #include <thrift/transport/TSocket.h>
 #include <thrift/transport/TTransportUtils.h>
 #include "gen-cpp/coordinator.h"
 
 using namespace std;
 using namespace apache::thrift;
 using namespace apache::thrift::protocol;
 using namespace apache::thrift::transport;
 
int main(int argc, char **argv) {
    if (argc < 6) {
        std::cout << "Usage: ./client <coordinator_ip> <coordinator_port> <dir_path> <rounds> <epochs>" << std::endl;
        return 1;
    }

    std::string coordinator_ip = argv[1];
    int coordinator_port = std::stoi(argv[2]);
    std::string dir_path = argv[3];
    int rounds = std::stoi(argv[4]);
    int epochs = std::stoi(argv[5]);

    std::shared_ptr<TTransport> socket(new TSocket(coordinator_ip, coordinator_port));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    coordinatorClient client(protocol);

    try {
        transport->open();
        std::cout << "Training with files in: " << dir_path << std::endl;
        std::cout << "rounds: " << rounds << std::endl;
        std::cout << "epochs: " << epochs << std::endl;
        std::cout << "h = 24, k = 26, eta = 0.0001\n";
        std::cout << "final validation error: " << client.train(dir_path, rounds, epochs, 24, 26, 0.0001) << std::endl;
        transport->close();
    } catch (TException& tx) {
        cout << "ERROR detected: " << tx.what() << endl;
    }
}
 