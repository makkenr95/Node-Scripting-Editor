#pragma once
#include "Vector3.hpp"
#include "Sphere.hpp"

namespace CommonUtilities
{
	template <class T>
	class Plane
	{
	public:
		Plane();
		Plane(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aPoint1, const CU::Vector3<T>& aPoint2);
		Plane(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aNormal);
		void InitWith3Points(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aPoint1,
							 const CU::Vector3<T>& aPoint2);
		void InitWithPointAndNormal(const CU::Vector3<T>& aPoint, const CU::Vector3<T>& aNormal);
		bool IsInside(const CU::Vector3<T>& aPosition) const;
		bool IsInside(const CommonUtilities::Sphere<T> aSphere);
		const CommonUtilities::Vector3<T>& GetNormal() const;
		const CU::Vector3<T>& GetPoint() const;
	private:
		CU::Vector3<T> myPoint;
		CU::Vector3<T> myNormal;
	};

	template <class T>
	Plane<T>::Plane()
	{
		myPoint = CU::Vector3<T>(0, 0, 0);
		myNormal = CU::Vector3<T>(0, 0, 0);
	}

	template <class T>
	Plane<T>::Plane(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aPoint1, const CU::Vector3<T>& aPoint2)
	{
		InitWith3Points(aPoint0, aPoint1, aPoint2);
	}

	template <class T>
	Plane<T>::Plane(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aNormal)
	{
		InitWithPointAndNormal(aPoint0, aNormal);
	}

	template <class T>
	void Plane<T>::InitWith3Points(const CU::Vector3<T>& aPoint0, const CU::Vector3<T>& aPoint1,
								   const CU::Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		CU::Vector3<T> dirA = aPoint1 - aPoint0;
		CU::Vector3<T> dirB = aPoint2 - aPoint0;
		myNormal = dirA.Cross(dirB).GetNormalized();
	}

	template <class T>
	void Plane<T>::InitWithPointAndNormal(const CU::Vector3<T>& aPoint, const CU::Vector3<T>& aNormal)
	{
		myPoint = aPoint;
		myNormal = aNormal.GetNormalized();
	}

	template <class T>
	bool Plane<T>::IsInside(const CU::Vector3<T>& aPosition) const
	{
		CU::Vector3<T> myDirection = aPosition - myPoint;
		if (myDirection.Dot(GetNormal()) <= 0)
		{
			return true;
		}
		return false;
	}

	template <class T>
	bool CommonUtilities::Plane<T>::IsInside(const CU::Sphere<T> aSphere)
	{
		CU::Vector3<float> distToCenter = aSphere.GetCenter() - myPoint;
		float dotProduct = distToCenter.Dot(myNormal);
		if (dotProduct <= 0)
		{
			return true;
		}
		distToCenter = dotProduct * myNormal;
		return distToCenter.Length() <= aSphere.GetRadius();
	}

	template <class T>
	const CU::Vector3<T>& Plane<T>::GetNormal() const
	{
		return myNormal.GetNormalized();
	}

	template <class T>
	const CU::Vector3<T>& Plane<T>::GetPoint() const
	{
		return myPoint;
	}
}

namespace CU = CommonUtilities;
