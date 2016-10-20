/*************************************************************************
    > File Name: main.cpp
    > Author: JTrancender
    > Email: jie-email@jie-trancender.org
    > Github: JieTrancender 
    > Created Time: Thu Oct 20 14:36:04 2016
 ************************************************************************/
#include <iostream>
#include <mutex>
#include <thread>

#include "simple_hierarchical_mutex.hpp"

mtp::HierarchicalMutex high_level_mutex(10000);
mtp::HierarchicalMutex low_level_mutex(5000);

int do_low_level_stuff()
{
	std::cout << __FILE__ << "#" << __LINE__ << ' ' << __FUNCTION__ << std::endl;
}

int low_level_func()
{
	std::lock_guard<mtp::HierarchicalMutex> lock(low_level_mutex);
	return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{
	std::cout << __FILE__ << "#" << __LINE__ << ' ' << __FUNCTION__ << std::endl;
}

void high_level_func()
{
	std::lock_guard<mtp::HierarchicalMutex> lock(high_level_mutex);
	high_level_stuff(low_level_func());
}

void thread_a()
{
	high_level_func();
}

mtp::HierarchicalMutex other_mutex(100);
void do_other_stuff()
{
	std::cout << __FILE__ << "#" << __LINE__ << ' ' << __FUNCTION__ << std::endl;
}

void other_stuff()
{
	high_level_func();
	do_other_stuff();
}

void thread_b()
{
	//在锁定较低互斥元other_mutex之后又调用high_level_func()函数锁定较高互斥元，违反层次。
	std::lock_guard<mtp::HierarchicalMutex> lock(other_mutex);
	other_stuff();
}

int main(int argc, char* arv[])
{
	std::thread t_one(thread_a);
	//std::thread t_two(thread_b);

	t_one.join();
	//t_two.join();
}
