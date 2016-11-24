/*************************************************************************
	> File Name: integer_split.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Nov 24 20:09:25 2016
 ************************************************************************/

#include<iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> vec;

int list[255];

void dfs(int x, int post)  //将x拿来分，分的最后一个数字为post
{
    int i;
    if (x == 0)
    {
        printf("%d", vec[0]);
        for (i = 1; i < vec.size(); ++i)
        {
            printf("+%d", vec[i]);
        }
        printf("\n");
    }

    for (i = x; i > 0; --i)
    {
        if (i <= post)
        {
            vec.push_back(i);
            dfs(x - i, i);
            vec.pop_back();
        }
    }
}

void split(int n, int m = 0)
{
    int i;
    if (n == 0)
    {
        for (i = 0; i < m; ++i)
        {
            printf("%d ", list[i]);
        }
        printf("\n");
        return;
    }

    for (i = n; i > 0; --i)
    {
        if (m == 0 || i <= list[m - 1])
        {
            list[m] = i;
            split(n - i, m + 1);
        }
    }
}

//p(n) = q(n, m)
int q(int n, int m)
{
    if (n < 1 || m < 1)
        return 0;
    if (n == 1 || m == 1)
        return 1;
    if (n < m)
        return q(n, n);
    if (n == m)
        return q(n, m - 1) + 1;
    return q(n, m - 1) + q(n - m, m);
}

int main()
{
    int n;

    int sum = q(5, 1) + q(4, 2) + q(3, 3) + q(2, 4) + q(1, 5);
    int count = 0;
    
    for (int i = 6, j = 1; i > 0; --i, ++j)
    {
        count += q(i, j);
    }
    printf("%d, %d\n", sum, count);

    while(~scanf("%d", &n))
    {
        dfs(n, n);
        printf("\n");
        split(n);
        printf("\n\n");
        printf("%d\n", q(n, n));
    }

    return 0;
}
