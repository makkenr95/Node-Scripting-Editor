#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template <class T>
	class Ray
	{
	public:
		Ray();
		Ray(const Ray<T>& aRay);
		Ray(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aPoint);
		void InitWith2Points(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aPoint);
		void InitWithOriginAndDirection(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aDirection);
		const CU::Vector3<T> GetDirection() const;
		const CU::Vector3<T> GetOrigin() const;
	private:
		CU::Vector3<T> myOrigin;
		CU::Vector3<T> myDirection;
	};

	template <class T>
	Ray<T>::Ray()
	{
		myOrigin = {0, 0, 0};
		myDirection = {0, 0, 0};
	}

	template <class T>
	Ray<T>::Ray(const Ray<T>& aRay)
	{
		myOrigin = aRay.myOrigin;
		myDirection = aRay.myDirection;
	}

	template <class T>
	Ray<T>::Ray(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - myOrigin;
		myDirection.Normalize();
	}

	template <class T>
	void Ray<T>::InitWith2Points(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - myOrigin;
		myDirection.Normalize();
	}

	template <class T>
	void Ray<T>::InitWithOriginAndDirection(const CU::Vector3<T>& aOrigin, const CU::Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}

	template <class T>
	const CU::Vector3<T> Ray<T>::GetDirection() const
	{
		return myDirection;
	}

	template <class T>
	const CU::Vector3<T> Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}
}

//namespace CommonUtilities = CU;
