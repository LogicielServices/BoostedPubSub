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
    size_t  recvDataLen = boost::asio::read(socket, boost::asio::buffer(recvBuffer,9));
    std::cout << "receiving data from server: ";
    std::cout.write(recvBuffer,recvDataLen);
    std::cout << std::endl;
}

void Client::insertIdInMap(std::string rcvdId, std::string symbol)
{
    clientMap.insert(std::pair<int, std::string>(std::stoi(rcvdId), symbol));
    for (const auto &[key, value]: clientMap) {
        std::cout << "Symbol [" << value << "] " << "is against id [" << key << "]" << std::endl;
    }
}


std::string Client::makeStreamFromMap(const std::map<int, std::string>& m)
{
    std::ostringstream oss;
    for (const auto& [key, value] : m)
    {
        oss << key << " " << value << "\n";
    }
    return oss.str();
}

void Client::writeStreamOnSocket(std::string stringOfMap)
{
    boost::asio::streambuf sendBuffer;
    std::ostream os(&sendBuffer);
    os << stringOfMap;
    boost::asio::write(socket, sendBuffer);
}



int main(int argc, char* argv[])
{
    std::string ip = argv[1];
    std::string port = argv[2];
    Client client;
    client.connect(ip,port);
    std::string receivedId = client.recvIdFromServer();
//    client.insertIdInMap(client.recvIdFromServer(),"IBM");
//    std::string stringOfMap = client.makeStreamFromMap(client.clientMap);

    std::string stringOfMap = receivedId.append("|IBM");
    client.writeStreamOnSocket(stringOfMap);
    client.recvDataFromServer();

    while(1){}

}