#pragma once
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;
		Vector2<T>();
		Vector2<T>(const T& aX, const T& aY);
		Vector2<T>(const Vector2<T>& aVector) = default;
		Vector2<T>& operator=(const Vector2<T>& aVector2);
		~Vector2<T>();
		T LengthSqr() const;
		T Length() const;
		Vector2<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector2<T>& aVector) const;
	};

	template <class T>
	Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template <class T>
	Vector2<T>::Vector2(const T& aX, const T& aY)
	{
		x = aX;
		y = aY;
	}

	template <class T>
	Vector2<T>& Vector2<T>::operator=(const Vector2<T>& aVector2)
	{
		x = aVector2.x;
		y = aVector2.y;
		return *this;
	}

	template <class T>
	Vector2<T>::~Vector2()
	{
	}

	template <class T>
	T Vector2<T>::LengthSqr() const
	{
		return x * x + y * y;
	}

	template <class T>
	T Vector2<T>::Length() const
	{
		return sqrt(x * x + y * y);
	}

	template <class T>
	Vector2<T> Vector2<T>::GetNormalized() const
	{
		if (x != 0 && y != 0)
		{
			T divider = 1 / Length();
			return Vector2(x * divider, y * divider);
		}
		return *this;
	}

	template <class T>
	void Vector2<T>::Normalize()
	{
		if (x != 0 && y != 0)
		{
			T divider = 1 / Length();
			x *= divider;
			y *= divider;
		}
	}

	template <class T>
	T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y;
	}

	template <class T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>&
						 aVector1)
	{
		return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
	}

	template <class T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>&
						 aVector1)
	{
		return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
	}

	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}

	template <class T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}

	template <class T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;
		return Vector2<T>(aVector.x * divider, aVector.y * divider);
	}

	template <class T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	template <class T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	template <class T>
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	template <class T>
	void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;
		aVector.x *= divider;
		aVector.y *= divider;
	}
}

namespace CU = CommonUtilities;
