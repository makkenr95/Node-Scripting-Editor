#pragma once
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		Vector3<T>();
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		Vector3<T>(const Vector3<T>& aVector) = default;
		Vector3<T>& operator=(const Vector3<T>& aVector3);
		~Vector3<T>();
		T LengthSqr() const;
		T Length() const;

		friend bool operator==(const Vector3& anLhs, const Vector3& anRhs)
		{
			return anLhs.x == anRhs.x
				&& anLhs.y == anRhs.y
				&& anLhs.z == anRhs.z;
		}

		friend bool operator!=(const Vector3& anLhs, const Vector3& anRhs)
		{
			return !(anLhs == anRhs);
		}

		Vector3<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector3<T>& aVector) const;
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};

	template <class T>
	Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template <class T>
	Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template <class T>
	Vector3<T>& Vector3<T>::operator=(const Vector3<T>& aVector3)
	{
		x = aVector3.x;
		y = aVector3.y;
		z = aVector3.z;
		return *this;
	}

	template <class T>
	Vector3<T>::~Vector3()
	{
	}

	template <class T>
	T Vector3<T>::LengthSqr() const
	{
		return x * x + y * y + z * z;
	}

	template <class T>
	T Vector3<T>::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	template <class T>
	Vector3<T> Vector3<T>::GetNormalized() const
	{
		if (x != 0 && y != 0 && z != 0)
		{
			T divider = 1 / Length();
			return Vector3(x * divider, y * divider, z * divider);
		}
		return *this;
	}

	template <class T>
	void Vector3<T>::Normalize()
	{
		if (x != 0 && y != 0 && z != 0)
		{
			T divider = 1 / Length();
			x *= divider;
			y *= divider;
			z *= divider;
		}
	}

	template <class T>
	T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return x * aVector.x + y * aVector.y + z * aVector.z;
	}

	template <class T>
	Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		return Vector3(
			y * aVector.z - z * aVector.y,
			z * aVector.x - x * aVector.z,
			x * aVector.y - y * aVector.x);
	}

	template <class T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>&
						 aVector1)
	{
		return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);
	}

	template <class T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>&
						 aVector1)
	{
		return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
	}

	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}

	template <class T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}

	template <class T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;
		return Vector3<T>(aVector.x * divider, aVector.y * divider, aVector.z * divider);
	}

	template <class T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	template <class T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	template <class T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	template <class T>
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		float divider = 1 / aScalar;
		aVector.x *= divider;
		aVector.y *= divider;
		aVector.z *= divider;
	}
}

namespace CU = CommonUtilities;
