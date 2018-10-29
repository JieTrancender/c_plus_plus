cmake_minimum_required (VERSION 2.8)

project (MUDUO C CXX)

#find_package(Boost REQUIRED)

add_executable(simple_echo echo/echo.cpp echo/main.cpp)
target_link_libraries(simple_echo muduo_net muduo_base pthread)

add_executable(simple_chargen chargen/chargen.cpp chargen/main.cpp)
target_link_libraries(simple_chargen muduo_net muduo_base pthread)

add_executable(simple_chargen_client chargenClient/chargenClient.cpp)
target_link_libraries(simple_chargen_client muduo_net muduo_base pthread)

add_executable(simple_time time/time.cpp time/main.cpp)
target_link_libraries(simple_time muduo_net muduo_base pthread)

add_executable(simple_time_client timeClient/main.cpp)
target_link_libraries(simple_time_client muduo_net muduo_base pthread)

add_executable(simple_day_time dayTime/dayTime.cpp dayTime/main.cpp)
target_link_libraries(simple_day_time muduo_net muduo_base pthread)

add_executable(simple_allinone allinone/main.cpp echo/echo.cpp chargen/chargen.cpp
	time/time.cpp dayTime/dayTime.cpp)
target_link_libraries(simple_allinone muduo_base muduo_net pthread)

#g++ -o echo echo.cpp main.cpp  -lmuduo_net -lmuduo_base -lpthread
# g++ -o chargen chargen.cpp main.cpp -lmuduo_net -lmuduo_base -lpthread