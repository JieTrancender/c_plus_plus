cmake_minimum_required (VERSION 2.8)

project (ASIO_CHAT_SERVER C CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(asio_chat_client client.cpp codec.hpp)
target_link_libraries(asio_chat_client muduo_base muduo_net pthread)

add_executable(asio_chat_server server.cpp codec.hpp)
target_link_libraries(asio_chat_server muduo_base muduo_net pthread)

add_executable(asio_chat_server_threaded serverThreaded.cpp codec.hpp)
target_link_libraries(asio_chat_server_threaded muduo_base muduo_net pthread)

add_executable(asio_chat_server_threaded_effiecient serverThreadedEfficient.cpp codec.hpp)
target_link_libraries(asio_chat_server_threaded_effiecient muduo_base muduo_net pthread)

add_executable(asio_chat_server_threaded_high_performance serverThreadedHighPerformance.cpp codec.hpp)
target_link_libraries(asio_chat_server_threaded_high_performance muduo_base muduo_net pthread)
