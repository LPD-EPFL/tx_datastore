/* 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ServerConnection.h"


ServerConnection::ServerConnection(std::string h, int prt) {
    boost::shared_ptr<TSocket> s(new TSocket(h, prt));
    boost::shared_ptr<TTransport> t(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> p(new TBinaryProtocol(transport));

    host = h;
    port = prt;
    socket = s;
    transport = t;
    protocol = p;

    client = new DataServerClient(protocol);

    transport->open(); //TODO is it a good idae to keep the transprot open all the time?

}

ServerConnection::~ServerConnection() {
    if (transport->isOpen()) {
        transport->close();
    }
}

