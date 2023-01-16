//
// Created by saad.hussain on 1/3/2023.
//
#include "publisher.h"

using boost::asio::ip::tcp;
//struct data{
//    int id;
//    char[10] topic;
//};
int Publisher::id = 1111;

void Publisher::doRead()
{
    std::cout << "Server reading from socket\n" << std::flush;
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(data),
                           [this](boost::system::error_code ec, std::size_t length)
                           {
                               if (!ec)
                               {
                                   std::cout << "data received from client is: " << data << std::endl;
                                   std::string stringData = data;
                                   std::vector<std::string> parsedData;
                                   boost::algorithm::split(parsedData, stringData,boost::is_any_of("|"));

                                   for(auto parsed: parsedData){
                                       std::cout << parsed << std::endl;
                                   }

//                                   filter.insert({std::stoi(parsedData[0]),parsedData[1]});
                                   filter.insert({parsedData[1], std::stoi(parsedData[0])});
//                                   publish("IBM");
                               }
                           });
}


void Publisher::publish(std::string symbol)
{
    auto it = filter.find(symbol);
    if (it != filter.end())
    {
        boost::asio::write(socket, boost::asio::buffer(symbol));
        std::cout << "Publishing IBM\n";
    }

}



void Publisher::sendId()
{
    std::cout << "Assigning ID " << id << " to client " << "\n" << std::flush;
    boost::asio::write(socket, boost::asio::buffer(std::to_string(id),std::to_string(id).size()));
    id++;
}


void Publisher::start()
{
    sendId();
    doRead();
//    publish("IBM");
    handleDisconnections();
}

void Publisher::handleDisconnections(){
    std::cout << "Disconnected\n" << std::flush;
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(data, max_length),
                            [this, self](boost::system::error_code error, size_t bytes_transferred)
                            {
                                if(error) // or some specific code
                                {
                                    std::cout << "Disconnected Id " << id << std::endl;
                                }
                                else
                                {
                                    std::cout << "Disconnected Id Else" << std::endl;
                                    // continue, launch new operation, etc
                                }
                            });

}




void Publisher::doWrite()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket, boost::asio::buffer(data),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/)
                             {
                                 if (!ec)
                                 {
                                     doRead();
                                 }
                             });
}



    void Session::accept()
    {
        std::cout << "Publisher is in accept state\n";
        acceptor.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::make_shared<Publisher>(std::move(socket))->start();
                    }
                    accept();
                });

    }


