//
// Created by saad.hussain on 1/3/2023.
//
#include "server.h"

using boost::asio::ip::tcp;
//struct data{
//    int id;
//    char[10] topic;
//};
int Session::id = 1111;

void Session::doRead()
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
                                   std::vector<std::string> parsed_data;
                                   boost::algorithm::split(parsed_data, stringData,boost::is_any_of("|"));

                                   for(auto parsed: parsed_data){
                                       std::cout << parsed << std::endl;
                                   }
                                   filter.insert({std::stoi(parsed_data[0]),parsed_data[1]});
                                   doWrite();
                               }
                           });
}
//std::map<int, char*> Session::makeMapFromStream(char* oss) {
//    int key;
//    char* value;
//    while (oss >> key) {
//        oss >> value;
//        map.insert(std::make_pair(key, value));
//    }
//    return map;
//}

void Session::sendId()
{
    std::cout << "Assigning ID " << id << " to client " << "\n" << std::flush;
    boost::asio::write(socket, boost::asio::buffer(std::to_string(id),std::to_string(id).size()));
    id++;
}
//void Session::publish()
//{
////    std::cout << "data: " << data;
//    std::map<int, std::string> map = makeMapFromStream(oss);
//    for (const auto& [key, value] : map)
//    {
//        std::cout << "key is [" << key << "]" << "value is [" << value << "]" << std::endl;
//    }
//}


void Session::start()
{
    sendId();
    doRead();
//    publish();
    handleDisconnections();
}

void Session::handleDisconnections(){
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




void Session::doWrite()
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



    void Server::accept()
    {
        std::cout << "Server is in accept state\n";
        acceptor.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket)
                {
                    if (!ec)
                    {
                        std::make_shared<Session>(std::move(socket))->start();
                    }
                    accept();
                });

    }



int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        Server s(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}