/*************************************************************************
	> File Name: find_location.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov 30 01:39:45 2016
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

bool find_flag = true;

namespace
{
    template <typename T, typename V>
    std::ptrdiff_t find_location(const T& value, const V& vec)
    {
        auto iter = std::find(vec.begin(), vec.end(), value);

        if (iter == vec.end())
        {
            find_flag = false;
        }
        return std::distance(vec.begin(), iter);
    }
}

int main(int argc, char* argv[])
{
    int n;
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 23, 23, 34, 4};

    std::cout << "Please input the num which you want to find:";
    std::cin >> n;

    auto num = find_location<int, std::vector<int>>(n, vec);

    if (find_flag)
    {
        std::cout << n << "'s location that being in vec is " << num << std::endl;
    }
    else
    {
        std::cout << "Can't find " << n << " in vec." << std::endl; 
    }
}
