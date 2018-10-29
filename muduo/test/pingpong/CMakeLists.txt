cmake_minimum_required (VERSION 2.8)

project(SIMPLE_PING_PONG C CXX)

add_executable(ping_pong_server server.cpp)
target_link_libraries(ping_pong_server muduo_base muduo_net pthread)

add_executable(ping_pong_client client.cpp)
target_link_libraries(ping_pong_client muduo_base muduo_net pthread)