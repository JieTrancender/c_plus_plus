/*************************************************************************
	> File Name: small_tools.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Sun Nov 20 19:50:09 2016
 ************************************************************************/

#include <iostream>
#include <boost/core/noncopyable.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>

using namespace boost;

namespace mtl
{
    class noncopyable
    {
    protected:
        noncopyable() = default;
        ~noncopyable() = default;

        noncopyable(const noncopyable&) = delete;
        const noncopyable& operator=(const noncopyable&) = delete;
    };

    struct none_helper(){};
    typedef int none_helper::*none_t;
    none_t const none = (static_cast<none_t>(0));  //定义常亮none

    //ignore_unused基本用法
    template <typename... T>
    inline void ignore_unused(T const& ...)
    {}

    //ignore_unused模板用法
    template <typename T>
    inline void ignore_unused()
    {}
}

class empty_class : public mtl::noncopyable
{};

int func(int x, int y)
{
    int i;
    mtl::ignore_unused(x, i);
    return y;
}

int func2()
{
    typedef int result_type;
    mtl::ignore_unused<result_type>();
}

int main(int argc, char* argv[])
{
    //empty_class empty_obj;
    //empty_class empty_obj1(empty_obj);
    func(3, 4);
    func2();

}

