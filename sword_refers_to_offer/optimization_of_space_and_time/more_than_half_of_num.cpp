/*************************************************************************
	> File Name: more_than_half_of_num.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Nov  1 18:31:50 2016
 ************************************************************************/

#include<iostream>

using namespace std;

int partition(int* num, int length, int start, int end)
{
    if (num == nullptr || length <= 0 || start < 0 || end >= length)
    {
        throw new std::exception("Invalid Parameters");  //不合法参数
    }

    int index = num[0];

    int small = start;
    for (index = start + 1; index < end; ++index)
    {
        if (num[index] < num[start])
        {
            ++small;
            if (index != start)
            {
                std::swap(num[index], num[small]);
            }
        }
    }

    ++small;
    std::swap(num[small], num[start]);

    return small;
}

bool g

int moreThanHalfOfNum(int* num, int length)
{
    if (checkInvalidArray(num, length))
        return 0;
}
