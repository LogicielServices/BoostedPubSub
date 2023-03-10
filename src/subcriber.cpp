//
// Created by saad.hussain on 1/5/2023.
//

#include "subcriber.h"

using  boost::asio::ip::tcp;

void Subscriber::connect(std::string ip, std::string port)
{
    tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
    boost::asio::connect(socket, endpoints);
    socket.set_option(boost::asio::socket_base::keep_alive(5));
}

std::string Subscriber::recvIdFromServer()
{
    size_t receivedIdLength = boost::asio::read(socket, boost::asio::buffer(receivedId, 4));
    std::string parsedId(receivedId, receivedIdLength);
    std::cout << "ID received from server is: " << parsedId << std::endl;
    return parsedId;
}

void Subscriber::recvDataFromServer()
{
    size_t  recvDataLen = boost::asio::read(socket, boost::asio::buffer(receivedData,32));
    std::cout.write(receivedData,recvDataLen);
    std::cout << std::endl;
}



void Subscriber::writeStreamOnSocket(std::string idAndSymbol)
{
    boost::asio::write(socket, boost::asio::buffer(idAndSymbol));
}

std::string Subscriber::appendSymbol(std::string receivedId)
{
    return receivedId.append("|IBM");
}


