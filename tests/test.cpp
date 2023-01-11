//
// Created by saad.hussain on 1/11/2023.
//

#define BOOST_TEST_MODULE PUBSUBTESTS
#include <boost/test/included/unit_test.hpp>
#include "../server.h"
#include "../client.h"
#include <boost/test/execution_monitor.hpp>

BOOST_AUTO_TEST_SUITE( SESSION )



BOOST_AUTO_TEST_CASE( CLIENT_CONNECTION_SUCCESS )
{
    std::thread serverThread =  std::thread ([]() {
        std::string ip = "127.0.0.1";
        short port = 3333;
        boost::asio::io_context io_context;
        Server server(io_context, port);
        io_context.run();

    });
    serverThread.detach();
    std::string ip = "127.0.0.1";
    std::string port = "3333";
    Client client;
    client.connect(ip,port);
    std::string receivedId = client.recvIdFromServer();
    BOOST_REQUIRE_EQUAL(receivedId, "1111");
    std::string stringOfMap = receivedId.append("|IBM");
    BOOST_REQUIRE_EQUAL(stringOfMap, "1111|IBM");
    client.writeStreamOnSocket(stringOfMap);

}




BOOST_AUTO_TEST_SUITE_END()