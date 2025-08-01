#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template <class T>
	class AABB3D
	{
	public:
		AABB3D();
		AABB3D(const AABB3D<T>& aAABB3D);
		AABB3D(const CU::Vector3<T>& aMin, const CU::Vector3<T>& aMax);
		void InitWithMinAndMax(const CU::Vector3<T>& aMin, const CU::Vector3<T>& aMax);
		bool IsInside(const CU::Vector3<T>& aPosition) const;
	private:
		CU::Vector3<T> myMin;
		CU::Vector3<T> myMax;
	};

	template <class T>
	AABB3D<T>::AABB3D()
	{
		myMin = {0, 0, 0};
		myMax = {0, 0, 0};
	}

	template <class T>
	AABB3D<T>::AABB3D(const AABB3D<T>& aAABB3D)
	{
		myMin = aAABB3D.myMin;
		myMax = aAABB3D.myMax;
	}

	template <class T>
	AABB3D<T>::AABB3D(const CU::Vector3<T>& aMin, const CU::Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	void AABB3D<T>::InitWithMinAndMax(const CU::Vector3<T>& aMin, const CU::Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	bool AABB3D<T>::IsInside(const CU::Vector3<T>& aPosition) const
	{
		if (myMin.x <= aPosition.x && myMax.x >= aPosition.x && myMin.z <= aPosition.y && myMax.y >= aPosition.y &&
			myMin.z <= aPosition.z && myMax.z >= aPosition.z)
		{
			return true;
		}
		return false;
	}
}

//namespace CommonUtilities = CU;
