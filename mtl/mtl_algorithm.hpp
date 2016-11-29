#pragma once

#include <algorithm>

namespace mtl
{
	template <typename Output, typename Size, typename T>
	Output fill_n(Output first, Size count, const T& value)
	{
		for (Size i = 0; i < count; ++i)
		{
			*first++ = value;	//++ÓÅÏÈ¼¶±È*¸ß
		}
		return first;
	}

	template <typename ForwardIt1, typename ForwardIt2>
	ForwardIt1 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2)
	{
		while (first1 != last1)
		{
			std::iter_swap(first1++, first2++);
		}
		return first2;
	}

	template <typename ForwardIt1, typename ForwardIt2>
	void iter_swap(ForwardIt1 a, ForwardIt2 b)
	{
		//using mtl::swap;
		using std::swap;
		swap(*a, *b);
	}

	template <typename T>
	void swap(T& a, T& b)
	{
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}

	template <typename InputIt1, typename InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			//only use < operator
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);	//because of operator <
	}

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

	template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
			{
				return false;
			}
		}
		return true;
	}

	template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		if (distance(first1, last1) != distance(first2, last2))
		{
			return false;
		}
		for (; first1 != last1, first2 != last2; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

}
