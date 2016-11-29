/*************************************************************************
	> File Name: number_of_partition.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov 30 00:40:47 2016
 ************************************************************************/

#include <iostream>

namespace
{
    std::size_t numberOfPartition(int n, int m)
    {
        if (m < 1 || n < 1)
        {
            return 0;
        }
        else if (m == 1 || n == 1)
        {
            return 1;
        }
        else if (n < m)
        {
            return numberOfPartition(n, n);
        }
        else if (n == m)
        {
            return numberOfPartition(n, m - 1) + 1;
        }
        else
        {
            return numberOfPartition(n, m - 1) + numberOfPartition(n - m, m);
        }
    }
}

int main(int argc, char* argv[])
{
    int n;

    std::cout << "Please input a integer num which needs to be divided: ";
    std::cin >> n;

    std::cout << n << " has " << numberOfPartition(n, n) << " kinds partition." << std::endl;
}
