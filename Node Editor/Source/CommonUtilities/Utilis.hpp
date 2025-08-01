#pragma once
#include <cassert>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <typename T>
	T Max(T a, T b)
	{
		if (a > b)
		{
			return a;
		}
		return b;
	}

	template <typename T>
	T Min(T a, T b)
	{
		if (a < b)
		{
			return a;
		}
		return b;
	}

	template <typename T>
	T Abs(T a)
	{
		if (a < 0)
		{
			return (a * -1);
		}
		return a;
	}

	template <typename T>
	T Clamp(T a, T b, T c)
	{
		assert(a <= b);
		if (c < a)
		{
			return a;
		}
		if (c > b)
		{
			return b;
		}
		return c;
	}

	template <typename T, typename T2>
	T Lerp(T a, T2 b, float t)
	{
		return a * (1 - t) + b * t;
	}

	template <typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
}
