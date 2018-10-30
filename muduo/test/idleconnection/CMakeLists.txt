cmake_minimum_required (VERSION 2.8)

project (ASIO_CHAT_SERVER C CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(idleconnection_echo echo.cpp main.cpp)
target_link_libraries(idleconnection_echo muduo_base muduo_net pthread)