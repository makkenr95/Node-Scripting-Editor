#pragma once
#include "Plane.hpp"
#include "Ray.hpp"
#include "AABB3D.hpp"
#include "Sphere.hpp"

namespace CommonUtilities
{
	template <typename T>
	bool IntersectionPlaneRay(const CU::Plane<T>& aPlane, const CU::Ray<T>& aRay,
							  CU::Vector3<T>& aOutIntersectionPoint);

	template <typename T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const CU::Ray<T>& aRay);

	template <typename T>
	bool IntersectionSphereRay(const CU::Sphere<T>& aSphere, const CU::Ray<T>& aRay);

	template <typename T>
	bool IntersectionPlaneRay(const CU::Plane<T>& aPlane, const CU::Ray<T>& aRay, CU::Vector3<T>& aOutIntersectionPoint)
	{
		T denom = aPlane.GetNormal().Dot(aRay.GetDirection());

		if (abs(denom) > 0.0001f)
		{
			T t = (aPlane.GetPoint() - aRay.GetOrigin()).Dot(aPlane.GetNormal()) / denom;
			if (t >= 0)
			{
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool IntersectionAABBRay(const CU::AABB3D<T>& aAABB, const CU::Ray<T>& aRay)
	{
		if (aAABB.IsInside(aRay.GetOrigin()))
		{
			return true;
		}
		return false;
	}

	template <typename T>
	bool IntersectionSphereRay(const CU::Sphere<T>& aSphere, const CU::Ray<T>& aRay)
	{
		CU::Ray<T> origi = aRay;
		CU::Vector3<T> originToSphere = aSphere.GetCenter() - aRay.GetOrigin();
		CU::Vector3<T> hej = aRay.GetDirection();
		T dotDir = originToSphere.Dot(aRay.GetDirection());

		if (dotDir <= 0.0f)
		{
			return false;
		}

		CU::Vector3<T> closestToSphere = aRay.GetDirection() * dotDir;

		return (originToSphere.LengthSqr() - closestToSphere.LengthSqr()) <= (aSphere.GetRadius() * aSphere.GetRadius()
		);

		return true;
	}
}

namespace CU = CommonUtilities;
