#pragma once
#include "Vector3.hpp"
#include "Plane.hpp"
#include <vector>

namespace CommonUtilities
{
	template <class T>
	class PlaneVolume
	{
	public:
		PlaneVolume() = default;
		explicit PlaneVolume(const std::vector<Plane<T>>& aPlaneList);
		void AddPlane(const Plane<T>& aPlane);
		bool IsInside(const Vector3<T>& aPosition);
		bool IsInside(CU::Sphere<T> aSphere);
	private:
		std::vector<Plane<T>> myPlanes;
	};

	template <class T>
	PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
	{
		myPlanes = aPlaneList;
	}

	template <class T>
	void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
	{
		myPlanes.push_back(aPlane);
	}

	template <class T>
	bool PlaneVolume<T>::IsInside(const Vector3<T>& aPosition)
	{
		for (size_t i = 0; i < myPlanes.size(); i++)
		{
			if (myPlanes[i].IsInside(aPosition) == false)
			{
				CU::Plane<T> h = myPlanes[i];
				return false;
			}
		}
		return true;
	}

	template <class T>
	bool PlaneVolume<T>::IsInside(CU::Sphere<T> aSphere)
	{
		for (size_t i = 0; i < myPlanes.size(); i++)
		{
			if (myPlanes[i].IsInside(aSphere) == false)
			{
				CU::Plane<T> h = myPlanes[i];
				return false;
			}
		}
		return true;
	}
}

namespace CU = CommonUtilities;
