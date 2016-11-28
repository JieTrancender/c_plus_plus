/*************************************************************************
	> File Name: array_test.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Mon Nov 28 17:01:44 2016
 ************************************************************************/

#include <iostream>
//#include <experimental/array>
#include <boost/array.hpp>

//using namespace std;
//using namespace boost;

void std_array_test()
{
    std::cout << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << std::endl;

    //member function: at, operator[], front, back, data, begin, cbegin, end, cend, rbegin, rend, crbegin, crend, empty, size, max_size, fill, swap
    std::array<int, 3> a1{1, 2, 3};
    std::array<int, 3> a2 = {1, 2, 3};
    std::array<std::string, 2> a3 = {std::string("abs"), "def"};
    //auto a4444 = std::experimental::make_array(1, 2, 3, 4, 5);
    //auto a4444 = std::make_array(1, 2, 3, 4, 5);

    std::sort(a1.begin(), a1.end());
    std::copy(a1.begin(), a1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    for (const auto& index : a3)
    {
        std::cout << index << ' ';
    }
    std::cout << std::endl;

    //std::copy(a4.begin(), a4.end(), std::ostream_iterator<int>(std::cout, " "));
    //std::cout << std::endl;
}

void boost_array_test()
{
    std::cout << __FILE__ << '#' << __LINE__ << " --- " << __FUNCTION__ << std::endl;

    boost::array<int, 10> ar;
    
    ar[0] = 1;
    ar.back() = 10;
    //boost::assert(ar[ar.max_size() - 1], 10);

    ar.assign(777);
    for (const auto& index : ar)
    {
        std::cout << index << ' ';
    }
    std::cout << std::endl;

    int *p = ar.c_array();
    *(p + 5) = 256;
    std::cout << ar[5] << std::endl;

    ar.at(8) = 666;
    std::sort(ar.begin(), ar.end());
    
    std::copy(ar.begin(), ar.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int a[10] = {0};
    boost::array<int, 10> arr = {0};
    assert(std::equal(arr.begin(), arr.end(), a));
}

int main(int argc, char* argv[])
{
    std_array_test();
    boost_array_test();
}

