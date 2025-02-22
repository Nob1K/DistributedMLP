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

 #include <thrift/protocol/TBinaryProtocol.h>
 #include <thrift/transport/TSocket.h>
 #include <thrift/transport/TTransportUtils.h>
 #include "ML.hpp"
 #include "gen-cpp/Compute.h"
 
 using namespace std;
 using namespace apache::thrift;
 using namespace apache::thrift::protocol;
 using namespace apache::thrift::transport;
 
 
 int main() {
   std::shared_ptr<TTransport> socket(new TSocket("localhost", 9000));
   std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
   std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
   ComputeClient client(protocol);
 
   try {
        transport->open();
        std::cout << client.check_availability() << std::endl;
        mlp almighty;
        almighty.init_training("../letters/train_letters1.txt", 26, 20);
        vector<vector<double>> v, w;
        almighty.get_weights(v, w);
        weights global = {};
        weights updated = {};
        global.v = v;
        global.w = w;
        client.train_model(updated, global, "../letters/train_letters1.txt", 0.001, 15);
        transport->close();
   } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
   }
 }
 