/*************************************************************************
	> File Name: max_numof_sub_sequence.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov 30 08:44:42 2016
 ************************************************************************/

#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

const int g_length = 100;
typedef std::vector<int> vecInt;

int findMaxNum(const vecInt& a, const vecInt& b)
{
    int c[g_length][g_length];

    //std::memcpy(c, 0, sizeof(c));
    for (int i = 0; i <= a.size(); ++i)
    {
        c[i][0] = 0;
    }

    for (int i = 0; i <= b.size(); ++i)
    {
        c[0][i] = 0;
    }

    for (int i = 1; i <= a.size(); ++i)
    {
        for (int j = 1; j <= b.size(); ++j)
        {
            if (a[i - 1] == b[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else
            {
                if (c[i - 1][j] >= c[i][j - 1])
                {
                    c[i][j] = c[i - 1][j];
                }
                else
                {
                    c[i][j] = c[i][j - 1];
                }
            }
        }
    }

    return c[a.size()][b.size()];
}

int main(int argc, char* argv[])
{
    vecInt a = {3, 34, 2, 5, 3, 4, 5, 6};
    vecInt b = {2, 3, 6, 5, 3, 5, 6, 6, 5};

    std::cout << "Max num of subsequence between a and b is " << findMaxNum(a, b) << std::endl;
}

