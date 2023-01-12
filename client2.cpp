//
// Created by saad.hussain on 1/5/2023.
//

#include "client.h"

using  boost::asio::ip::tcp;

void Client::connect(std::string ip, std::string port)
{
    tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
    boost::asio::connect(socket, endpoints);
    socket.set_option(boost::asio::socket_base::keep_alive(5));
}

std::string Client::recvIdFromServer()
{
    size_t receivedIdLength = boost::asio::read(socket, boost::asio::buffer(receivedId, 4));
    std::cout << "ID received from server is: ";
    std::cout.write(receivedId, receivedIdLength);
    std::cout << std::endl;
    return receivedId;
}

void Client::recvDataFromServer()
{
    size_t  recvDataLen = boost::asio::read(socket, boost::asio::buffer(receivedData,9));
    std::cout << "receiving data from server: ";
    std::cout.write(receivedData,recvDataLen);
    std::cout << std::endl;
}



void Client::writeStreamOnSocket(std::string idAndSymbol)
{
    boost::asio::streambuf sendBuffer;
    std::ostream os(&sendBuffer);
    os << idAndSymbol;
    boost::asio::write(socket, sendBuffer);
}



int main(int argc, char* argv[])
{
    std::string ip = argv[1];
    std::string port = argv[2];
    Client client;
    client.connect(ip,port);
    std::string receivedId = client.recvIdFromServer();
    std::string appendedStrToSend = receivedId.append("|IBM");
    client.writeStreamOnSocket(appendedStrToSend);
    client.recvDataFromServer();

    while(1){}

}