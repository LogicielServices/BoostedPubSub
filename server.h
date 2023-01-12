//
// Created by saad.hussain on 1/3/2023.
//

#ifndef ASIOCLIENTSERVER_SERVER_H
#define ASIOCLIENTSERVER_SERVER_H
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <map>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port)
    : acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        accept();
    }
private:
    void accept();
    tcp::acceptor acceptor;
};

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket)
    : socket(std::move(socket))
    {
//        socket.set_option(boost::asio::socket_base::keep_alive(5));
    }
    void start();
private:
    void handleDisconnections();
    void doRead();
    void publish();
    void sendId();
    void doWrite();
    tcp::socket socket;
    enum { max_length = 1024 };
    char data[max_length];
//    std::unordered_map<int, std::string> filter;
    std::unordered_map<std::string, int> filter;
    int static id;


};

#endif //ASIOCLIENTSERVER_SERVER_H
