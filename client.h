//
// Created by saad.hussain on 1/3/2023.
//

#ifndef ASIOCLIENTSERVER_CLIENT_H
#define ASIOCLIENTSERVER_CLIENT_H
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <map>
#include <sstream>
using  boost::asio::ip::tcp;

class Client {
public:
    boost::asio::io_context ioContext;
    tcp::socket socket;
    tcp::resolver resolver;
    std::map<int, std::string> clientMap;
    char receivedId[4];
    char recvBuffer[9];
public:
    Client()  :
            ioContext(),
            socket(ioContext),
            resolver(ioContext)
    {}
    void connect(std::string ip, std::string port);
    std::string recvIdFromServer();
    void insertIdInMap(std::string rcvdId, std::string symbol);
    std::string makeStreamFromMap(const std::map<int, std::string>& m);
    void writeStreamOnSocket(std::string stringOfMap);
    void recvDataFromServer();
};


#endif //ASIOCLIENTSERVER_CLIENT_H
