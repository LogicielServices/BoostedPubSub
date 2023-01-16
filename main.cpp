#include <iostream>
#include "server.h"
#include "client.h"
#include <thread>


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: async_tcp_echo_server <port>\n";
        return 1;
    }

    std::thread pubThread = std::thread([=]() {
        boost::asio::io_context io_context;

        Server s(io_context, std::atoi(argv[2]));
        io_context.run();
    });
    pubThread.detach();

    std::string ip = argv[1];
    std::string port = argv[2];
    Client client;
    client.connect(ip,port);
    std::string receivedId = client.recvIdFromServer();
    std::string appendedStrToSend = client.appendSymbol(receivedId);
    client.writeStreamOnSocket(appendedStrToSend);
    client.recvDataFromServer();
    while(1) {}
    return 0;
}
