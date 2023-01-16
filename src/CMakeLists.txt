
include_directories(include)
add_executable(pubsub ../main.cpp client.cpp server.cpp)

target_link_libraries(pubsub -lboost_system pthread)