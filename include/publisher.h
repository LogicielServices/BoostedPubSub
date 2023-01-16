//
// Created by saad.hussain on 1/3/2023.
//

#ifndef ASIOCLIENTSERVER_PUBLISHER_H
#define ASIOCLIENTSERVER_PUBLISHER_H
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <map>
#include <boost/algorithm/string.hpp>
#include <functional>

using boost::asio::ip::tcp;

class Session {
public:
    Session(boost::asio::io_context& io_context, short port)
    : acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        accept();
    }

private:
    void accept();
    tcp::acceptor acceptor;
};







class Publisher : public std::enable_shared_from_this<Publisher>
{
public:
    Publisher(tcp::socket socket)
    : socket(std::move(socket))
    {}
    void start();
    void publish(std::string);
private:
    void handleDisconnections();
    void doRead();
    void sendId();
    void doWrite();
    tcp::socket socket;
    enum { max_length = 1024 };
    char data[max_length];
    std::unordered_map<std::string, int> filter;
    int static id;
    bool flag = true;


};

#endif //ASIOCLIENTSERVER_PUBLISHER_H
