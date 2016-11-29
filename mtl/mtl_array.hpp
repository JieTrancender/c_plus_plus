#pragma once

#include "mtl_memory.hpp"

#include <cstdio>
#include <memory>
#include <iterator>
#include <exception>

namespace mtl
{
	template <typename _Tp, std::size_t _Nm>
	struct _array_traits
	{
		typedef _Tp _Type[_Nm];

		static constexpr _Tp& _S_ref(const _Type& _t, std::size_t _n) noexcept
		{
			return const_cast<_Tp&>(_t[_n]);
		}
	};

	template <typename _Tp>
	struct _array_traits<_Tp, 0>
	{
		struct _Type {};

		static constexpr _Tp& _S_ref(const _Type&, std::size_t) noexcept
		{
			return *static_cast<_Tp*>(nullptr);
		}
	};

	template <typename _Tp, std::size_t _Nm>
	struct array
	{
		typedef _Tp value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* iterator;
		typedef const value_type* const_iterator;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef _array_traits<_Tp, _Nm> _AT_Type;
		typename _AT_Type::_Type _M_elems;

		void fill(const value_type& _u)
		{
			//mtl::fill_n(begin(), size(), _u);
			std::fill_n(begin(), size(), _u);
		}
		
		//https://zh.cppreference.com/w/cpp/utility/declval
		void swap(array& _other) noexcept(noexcept(swap(std::declval<_Tp&>(), std::declval<_Tp&>())))
		{
			std::swap_ranges(begin(), end(), _other.begin());
		}

		iterator begin() noexcept
		{
			return iterator(data());
		}

		const_iterator begin() const noexcept
		{
			return const_iterator(data());
		}

		iterator end() noexcept
		{
			return iterator(data() + _Nm);
		}

		const_iterator end() const noexcept
		{
			return const_iterator(data() + _Nm);
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(begin());
		}

		const_iterator cbegin() const noexcept
		{
			return const_iterator(data());
		}

		const_iterator cend() const noexcept
		{
			return const_iterator(data() + _Nm);
		}

		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(begin());
		}

		constexpr size_type size() const noexcept
		{
			return _Nm;
		}

		constexpr size_type max_size() const noexcept
		{
			return _Nm;
		}

		constexpr bool empty() const noexcept
		{
			return size() == 0;
		}

		reference operator[](size_type _n)
		{
			return _AT_Type::_S_ref(_M_elems, _n);
		}

		constexpr const_reference operator[](size_type _n) const noexcept
		{
			return _AT_Type::_S_ref(_M_elems, _n);
		}

		reference at(size_type _n)
		{
			if (_n > _Nm)
			{
                //throw std::out_of_range(_N("array::at"));
                throw std::out_of_range("array::at");
			}
			return _AT_Type::_S_ref(_M_elems, _n);
		}

		constexpr const_reference at(size_type _n) const
		{
			//return _n < _Nm ? _AT_Type::_S_ref(_M_elems, _n) : (std::throw_with_nested out_of_range(_N("array::at")), _AT_Type::_S_ref(_M_elems, 0));
            return _n < _Nm ? _AT_Type::_S_ref(_M_elems, _n) : (throw std::out_of_range("array::at"), _AT_Type::_S_ref(_M_elems, 0));
		}

		reference front()
		{
			return *begin();
		}

		constexpr const_reference front()
		{
			return _AT_Type::_S_ref(_M_elems, 0);
		}

		reference back()
		{
			return _Nm ? *(end() - 1) : *end();
		}

		constexpr const_reference back()
		{
			return _Nm ? _AT_Type::_S_ref(_M_elems, _Nm - 1) : _AT_Type::_S_ref(_M_elems, 0);
		}

		pointer data() noexcept
		{
			//return mtl::addressof(_AT_Type::_S_ref(_M_elems, 0));
			return std::addressof(_AT_Type::_S_ref(_M_elems, 0));
		}

		const_pointer data() const noexcept
		{
			return std::addressof(_AT_Type::_S_ref(_M_elems, 0));
		}
	};	//end of array

	template <typename _Tp, std::size_t _Nm>
	inline bool operator==(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		return std::equal(_a.begin(), _a.end(), _b.begin());
	}

	template <typename _Tp, std::size_t _Nm>
	inline bool operator!=(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		return !(_a == _b);
	}

	template <typename _Tp, std::size_t _Nm>
	inline bool operator<(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		//return mtl::lexicographical_compare(_a.begin(), _a.end(), _b.begin(), _b.end());
		return std::lexicographical_compare(_a.begin(), _a.end(), _b.begin(), _b.end());
	}

	template <typename _Tp, std::size_t _Nm>
	inline bool operator>(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		return _b < _a;
	}

	template <typename _Tp, std::size_t _Nm>
	inline bool operator<=(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		return !(_a > _b);
	}

	template <typename _Tp, std::size_t _Nm>
	inline bool operator>=(const array<_Tp, _Nm>& _a, const array<_Tp, _Nm>& _b)
	{
		return !(_a < _b);
	}

	template <typename _Tp, std::size_t _Nm>
	inline void swap(array<_Tp, _Nm>& _a, array<_Tp, _Nm>& _b) noexcept(noexcept(_a.swap(_b)))
	{
		_a.swap(_b);
	}

	template <std::size_t _Int, typename _Tp, std::size_t _Nm>
	constexpr _Tp& get(array<_Tp, _Nm>& _arr) noexcept
	{
		static_assert(_Int < _Nm, "index is out of bounds");
		return _array_traits<_Tp, _Nm>::_S_ref(_arr._M_elems, _Int);
	}

	template <std::size_t _Int, typename _Tp, std::size_t _Nm>
	constexpr _Tp&& get(array<_Tp, _Nm>&& _arr) noexcept
	{
		static_assert(_Int < _Nm, "index is out of bounds");
		return std::move(get<_Int>(_arr));
	}

	template <std::size_t _Int, typename _Tp, std::size_t _Nm>
	constexpr const _Tp& get(const array<_Tp, _Nm>& _arr) noexcept
	{
		static_assert(_Int < _Nm, "index is out of bounds");
		return _array_traits<_Tp, _Nm>::_S_ref(_arr._M_elems, _Int);
	}
}
