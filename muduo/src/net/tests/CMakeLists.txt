cmake_minimum_required (VERSION 2.8)

project (MUDUO_NET_TEST C CXX)

add_executable(bufferUnitTest bufferUnitTest.cpp)
target_link_libraries(bufferUnitTest muduo_net muduo_base pthread boost_unit_test_framework)