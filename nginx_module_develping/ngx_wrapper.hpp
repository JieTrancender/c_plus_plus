#pragma once

#include <boost/type_traits.hpp>

//nmd stand for nginx module developing
namespace nmd
{
    template <typename T>
    class NgxWrapper
    {
    public:
        typedef typename boost::remove_pointer<T>::type wrapped_type;  //元函数消除类型里的指针修饰

        typedef wrapped_type* pointer_type;
        typedef wrapped_type& reference_type;

        pointer_type get() const
        {
            return m_ptr;
        }

        operator bool() const
        {
            return get();
        }

        operator pointer_type() const
        {
            return get();
        }

        pointer_type operator->() const
        {
            return get();
        }

    protected:  //因为只能被继承用，所以成员函数都放在protected里面
        NgxWrapper(pointer_type p) : m_ptr(p) {}  //函数体无内容

        NgxWrapper(reference_type x) : m_ptr(&x) {}  //函数体无内容

        ~NgxWrapper() = default;  //NgxWrapper不负责对象的生命周期管理，所以析构函数不删除指针


    private:
        pointer_type m_ptr = nullptr;
    };
}
