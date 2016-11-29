/*************************************************************************
	> File Name: tower_of_hanoi.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov 30 00:54:56 2016
 ************************************************************************/

#include <iostream>
#include <functional>

template <typename T>
inline void print(const T& a, const T& b, const int& n)
{
    std::cout << "Move disk" << n << " from " << a << " to " << b << std::endl;
}

//void moveDisks(const T&a, const T& b, const T& c, const int& n)
template <typename T>
void moveDisks(const T& a, const T& b, const T& c, const int& n)
{
    if (1 == n)
    {
        print(a, c, n);
    }
    else
    {
        moveDisks(a, c, b, n - 1);
        print(a, c, n);
        moveDisks(b, a, c, n - 1);
    }
}

int main(int argc, char* argv[])
{
    int n;
    char ch[3] = {'A', 'B', 'C'};

    std::cout << "Please input the count of disk:";
    std::cin >> n;

    moveDisks<char>(ch[0], ch[1], ch[2], n);
}
