/*************************************************************************
	> File Name: small_tools.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Sun Nov 20 19:50:09 2016
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
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

    struct none_helper{};
    typedef int none_helper::*none_t;
    none_t const none = (static_cast<none_t>(0));  //定义常亮none

    template <typename T>
    class optional
    {
    public:
        optional();
        optional(none_t);
        optional(T const& v);
        optional(bool condition, T v);

        optional& operator=(T const& rhs);

        template <typename... Args>
        void emplace(Args...&& args);

        T* operator->();
        T& operator*();

        T& get();
        T* get_ptr();

        T& value();
        T const& value_or(T const& default) const;
        template <typename F>
        T value_or_eval(F f) const;

        explicit operator bool() const;
        bool operator!() const;
    };

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
    //func(3, 4);
    //func2();

    optional<int> op0;
    optional<int> op1(none);

    assert(!op0);
    assert(op0 == op1);

    assert(op1.value_or(253) == 253);
    std:cout << op1.value_or_eval([](){ return 874;  }) << std::endl;

    optional<std::string> ops("test");
    std:cout << *ops << std::endl;

    ops.emplace("monado", 3);
    assert(*ops == "mon");

    std::vector<int> v(10);
    optional<std::vector<int>& > opv(v);
    assert(opv);

    opv->push_back(5);
    assert(opv->size() == 11);

    opv = none;
    assert(!opv);

}

