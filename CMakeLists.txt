cmake_minimum_required(VERSION 3.20)
project(asioClientServer)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED)


add_executable(server server.cpp)
add_executable(client client.cpp )
add_executable(client2 client2.cpp )
add_executable(syncClient syncClient.cpp)
add_executable(syncServer syncServer.cpp)
add_executable(AsyncClient AsyncClient.cpp)

target_link_libraries(server -lboost_system pthread)
target_link_libraries(client -lboost_system pthread)
target_link_libraries(client2 -lboost_system pthread)
target_link_libraries(syncClient -lboost_system pthread)
target_link_libraries(syncServer -lboost_system pthread)
target_link_libraries(AsyncClient -lboost_system pthread)
