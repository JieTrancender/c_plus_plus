cmake_minimum_required (VERSION 2.8)

project(filetransfer C CXX)

add_executable(filetransfer_all_in downloadAllIn.cpp)
target_link_libraries(filetransfer_all_in muduo_base muduo_net pthread)

add_executable(filetransfer_part_in downloadPartIn.cpp)
target_link_libraries(filetransfer_part_in muduo_base muduo_net pthread)

add_executable(filetransfer_rall downloadRall.cpp)
target_link_libraries(filetransfer_rall muduo_base muduo_net pthread)