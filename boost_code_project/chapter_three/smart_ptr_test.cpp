/*************************************************************************
	> File Name: smart_ptr_test.cpp
	> Author: JieTrancender
	> Mail: jie-email@jie-trancender.org
	> Created Time: Wed Nov  9 22:14:22 2016
 ************************************************************************/

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>

//using namespace std;
//using namespace boost;

namespace mtl
{
    template <typename T>
    class scoped_ptr
    {
    private:
        T *px;
        scoped_ptr(scoped_ptr const &);
        scoped_ptr& operator=(scoped_ptr const &);

        void operator==(scoped_ptr const &) const;
        void operator!=(scoped_ptr const &) const;
        
    public:
        explicit scoped_ptr(T *p = 0);
        ~scoped_ptr();

        void reset(T *p = 0);
        T& operator*() const;
        T* operator->() const;
        T* get() const;

        explicit operator bool() const;  //显式bool值转型
        void swap(scoped_ptr &b);
    };

    template <typename T>
    inline bool operator==(scoped_ptr<T> const &p, boost::detail::sp_nullptr_t);  //与空指针比较  sp_nullptr_t <=> std::nullptr_t

    template <typename T, typename D = std::default_delete<T>>
    class unique_ptr
    {
    public:
        typedef T* pointer;
        typedef T element_type;

        constexpr unique_ptr() noexcept;
        explicit unique_ptr(pointer p) noexcept;

        ~unique_ptr();
        unique_ptr& operator=(unique_ptr &&u) noexcept;  //移动语义赋值

        element_type& operator*() const;
        pointer operator->() const noexcept;
        pointer get() const noexcept;
        explicit operator bool() const noexcept;

        pointer release() noexcept;
        void reset(pointer p) noexcept;
        void swap(unique_ptr &u) noexcept;

        unique_ptr(const unique_ptr &) = delete;
        unique_ptr& operator=(const unique_ptr &) = delete;
    };

    template <typename T>
    bool operator==(const unique_ptr<T> &x, const unique_ptr<T> &y);

    template <typename T>
    class scoped_array
    {
    public:
        explicit scoped_array(T *p = 0);
        ~scoped_array();

        void reset(T *p = 0);
        T& operator[](std::ptrdiff_t i) const;
        T* get() const;

        explicit operator bool() const;
        void swap(scoped_array &b);
    };

    template <typename T, typename D>
    class unique_ptr<T[], D>
    {
    public:
        typedef T* pointer;
        typedef T element_type;

        explicit unique_ptr() noexcept;
        explicit unique_ptr(pointer p) noexcept;

        ~unique_ptr();

        T& operator[](size_t i) const;
        pointer get() const;
        explicit operator bool() const noexcept;

        pointer release() noexcept;
        void reset(pointer p) noexcept;

        void swap(unique_ptr &u) noexcept;

        unique_ptr(const unique_ptr &) = delete;
        unique_ptr& operator=(const unique_ptr &) = delete;
    };

    template <typename T>
    class shared_ptr
    {
    public:
        typedef T element_type;
        shared_ptr();

        template <typename Y> explicit shared_ptr(Y *p);
        template <typename Y, typename D> shared_ptr(Y *p, D d);

        ~shared_ptr();

        shared_ptr(shared_ptr const &r);

        shared_ptr& operator=(shared_ptr const &r);
        template <typename Y> shared_ptr& operator=(shared_ptr<Y> const &r);

        void reset();
        template <typename Y> void reset(Y *p);
        template <typename Y, typename D> void reset(Y *p, D d);

        T& operator*() const;
        T* operator->() const;
        T* get() const;

        bool unique() const;  //是否唯一
        long use_count() const;  //引用计数

        explicit operator bool() const;
        void swap(shared_ptr &b);
    };
}

class shared
{
private:
    std::shared_ptr<int> p;
public:
    shared(std::shared_ptr<int> p_) : p(p_) {}

    void print()
    {
        std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
    }
};

void print_func(std::shared_ptr<int> p)
{
    std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
}

int main()
{
    using namespace boost;

    scoped_ptr<std::string> sp(new std::string("text"));
    assert(sp);
    assert(sp != nullptr);
    std::cout << *sp << std::endl;
    std::cout << sp->size() << std::endl;

    std::unique_ptr<int> up(new int);
    assert(up);
    *up = 10;
    std::cout << *up << std::endl;
    up.reset();
    assert(!up);

    auto p = make_unique<int>(20);
    std::cout << *p << std::endl;

    int *arr = new int[100];
    scoped_array<int> sa(arr);
    std::fill_n(&sa[0], 100, 5);  //标准库算法赋值
    sa[10] = sa[20] + sa[30];

    std::unique_ptr<int[]> upa(new int[10]);
    upa[30] = 10;
    std::cout << upa[30] << std::endl;

    std::shared_ptr<int> spi(new int);
    assert(spi);
    *spi = 253;

    std::shared_ptr<std::string> sps(new std::string("smart"));
    assert(sps->size() == 5);

    //shared_ptr<int> dont_do_this(new int[10]);  //这样做会发生内存泄漏，因为不能正确释放内存
    
    std::shared_ptr<int> spInt(new int(10));
    assert(spInt.unique());
    std::shared_ptr<int>spInt2 = spInt;
    assert(spInt == spInt2 && spInt.use_count() == 2);

    *spInt2 = 100;
    std::cout << spInt << ' ' << spInt2 << std::endl;
    assert(*spInt == 100);
    spInt.reset();
    assert(!spInt);

    std::shared_ptr<int> pInt(new int(100));
    shared s1(pInt), s2(pInt);

    s1.print();
    s2.print();

    *pInt = 20;
    print_func(pInt);
    s1.print();
}

