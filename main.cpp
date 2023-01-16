#include <iostream>
#include "include/server.h"
#include "include/client.h"
#include <thread>


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: async_tcp_echo_server <port>\n";
        return 1;
    }

    std::thread publisherThread = std::thread([=]() {
        boost::asio::io_context io_context;

        Publisher s(io_context, std::atoi(argv[2]));
        io_context.run();
    });
    publisherThread.detach();

    std::string ip = argv[1];
    std::string port = argv[2];
    Subscriber subscriber;
    subscriber.connect(ip,port);
    std::string receivedId = subscriber.recvIdFromServer();
    std::string appendedStrToSend = subscriber.appendSymbol(receivedId);
    subscriber.writeStreamOnSocket(appendedStrToSend);
    subscriber.recvDataFromServer();
    while(1) {}
    return 0;
}
