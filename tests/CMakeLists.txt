add_executable(testmain  ../server.cpp ../client2.cpp test.cpp)
target_link_libraries(testmain  -lboost_system pthread )



