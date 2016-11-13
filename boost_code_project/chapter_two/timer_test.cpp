/*************************************************************************
	> File Name: timer_test.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov  9 21:17:36 2016
 ************************************************************************/

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <boost/timer.hpp>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;

//mtl stand for my test library
namespace mtl
{
    //boost::timer的实现
    class timer// final
    {
    public:
        timer()
        {
            _start_time = std::clock();
        }

        ~timer() = default;

        void restart()
        {
            _start_time = std::clock();
        }

        double elapsed() const
        {
            return double(std::clock() - _start_time) / CLOCKS_PER_SEC;  //CLOCKS_PER_SEC定义每秒的clock数
        }

        double elapsed_min() const
        {
            return double(double(1) / double(CLOCKS_PER_SEC));
        }

        double elapsed_max() const
        {
            return (double((std::numeric_limits<std::clock_t>::max)()) - double(_start_time)) / double(CLOCKS_PER_SEC);
        }

    private:
        std::clock_t _start_time;
    };
}

int main()
{
    timer t;

    cout << "max timerspan: " << t.elapsed_max() / 3600 << 'h' << endl;  //可度量的最大时间
    cout << "min timerspan: " << t.elapsed_min() << 's' << endl;
    cout << "now time elapsed: " << t.elapsed() << 's' << endl;

    mtl::timer timer;
    cout << "max timerspan: " << timer.elapsed_max() / 3600 << 'h' << endl;

    vector<string> v(100, "jie-email@jie-trancender.org");
    ofstream fs("./test.txt");
    progress_display pd(v.size());

    v[10] = "";
    v[34] = "";

    /*for (auto& x : v)
    {
        fs << x << endl;
        ++pd;
    }*/
    for (auto pos = v.begin(); pos != v.end(); ++pos)
    {
        fs << *pos << endl;
        ++pd;

        //pd.restart(v.size());
        //pd += (pos - v.begin() + 1);

        if (pos->empty())
        {
            cout << "null string #" << (pos - v.begin()) << endl;
        }
    }
}

