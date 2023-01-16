
include_directories(include)
add_executable(pubsub ../main.cpp subcriber.cpp publisher.cpp)

target_link_libraries(pubsub -lboost_system pthread)