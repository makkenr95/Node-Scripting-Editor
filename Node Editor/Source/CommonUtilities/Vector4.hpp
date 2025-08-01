#pragma once
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;
		Vector4<T>();
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);
		Vector4<T>(const Vector4<T>& aVector) = default;
		Vector4<T>& operator=(const Vector4<T>& aVector4);
		~Vector4<T>();
		T LengthSqr() const;
		T Length() const;
		Vector4<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector4<T>& aVector) const;
	};

	template <class T>
	Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template <class T>
	Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template <class T>
	Vector4<T>& Vector4<T>::operator=(const Vector4<T>& aVector4)
	{
		x = aVector4.x;
		y = aVector4.y;
		z = aVector4.z;
		w = aVector4.w;
		return *this;
	}

	template <class T>
	Vector4<T>::~Vector4()
	{
	}

	template <class T>
	T Vector4<T>::LengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <class T>
	T Vector4<T>::Length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	template <class T>
	Vector4<T> Vector4<T>::GetNormalized() const
	{
		if (x != 0 && y != 0 && z != 0 && w != 0)
		{
			T divider = 1 / Length();
			return Vector4(x * divider, y * divider, z * divider, w * divider);
		}
		return *this;
	}

	template <class T>
	void Vector4<T>::Normalize()
	{
		if (x != 0 && y != 0 && z != 0 && w != 0)
		{
			T divider = 1 / Length();
			x *= divider;
			y *= divider;
			z *= divider;
			w *= divider;
		}
	}

	template <class T>
	T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y + z * aVector.z + w * aVector.w;
	}


	template <class T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>&
						 aVector1)
	{
		return Vector4<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z,
						  aVector0.w + aVector1.w);
	}

	template <class T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>&
						 aVector1)
	{
		return Vector4<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z,
						  aVector0.w - aVector1.w);
	}

	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}

	template <class T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}

	template <class T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;

		return Vector4<T>(aVector.x * divider, aVector.y * divider, aVector.z * divider, aVector.w * divider);
	}

	template <class T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	template <class T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	template <class T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	template <class T>
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;
		aVector.x *= divider;
		aVector.y *= divider;
		aVector.z *= divider;
		aVector.w *= divider;
	}
}

namespace CU = CommonUtilities;
