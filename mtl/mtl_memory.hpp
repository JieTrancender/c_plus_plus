#pragma once

namespace mtl
{
	template <typename T>
	T* addressof(T& arg)
	{
		return reinterpret_cast<T*>(&const_cast<char&>(reinterprt_cast<const volatile char&>(arg)));
	}
}
