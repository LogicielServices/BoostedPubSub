//
// Created by saad.hussain on 1/3/2023.
//

#ifndef ASIOCLIENTSERVER_SUBCRIBER_H
#define ASIOCLIENTSERVER_SUBCRIBER_H
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <map>
#include <sstream>
using  boost::asio::ip::tcp;

class Subscriber {
public:
    boost::asio::io_context ioContext;
    tcp::socket socket;
    tcp::resolver resolver;

public:
    Subscriber()  :
            ioContext(),
            socket(ioContext),
            resolver(ioContext)
    {}
    void connect(std::string ip, std::string port);
    std::string recvIdFromServer();
    void writeStreamOnSocket(std::string idAndSymbol);
    void recvDataFromServer();
    std::string appendSymbol(std::string receivedId);
private:
    enum { max_length = 1024 };
    char receivedData[max_length];
    char receivedId[max_length];
};


#endif //ASIOCLIENTSERVER_SUBCRIBER_H
