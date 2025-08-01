#pragma once
#include <cmath>
#include "Vector2.hpp"

namespace CommonUtilities
{
	template <class T>
	class Line
	{
	public:
		Line() = default;
		Line(const Line<T>& aLine);
		Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1);
		void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);
		bool IsInside(const Vector2<T>& aPosition) const;
		const Vector2<T>& GetDirection() const;
		const Vector2<T> GetNormal() const;
	private:
		Vector2<T> myPoint = Vector2<T>(0, 0);
		Vector2<T> myDirection = Vector2<T>(0, 0);
	};

	template <class T>
	Line<T>::Line(const Line<T>& aLine)
	{
		myPoint = aLine.myPoint;
		myDirection = aLine.myDirection;
	}

	template <class T>
	Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myPoint = aPoint0;
		myDirection = aPoint1 - aPoint0;
	}

	template <class T>
	bool operator==(const Line<T>& aLine, const Line<T>& aLine1)
	{
		if (aLine == aLine1)
		{
			return true;
		}
		return false;
	}

	template <class T>
	void Line<T>::InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myPoint = aPoint0;
		myDirection = aPoint1 - aPoint0;
	}

	template <class T>
	void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myPoint = aPoint;
		myDirection = aDirection.GetNormalized();
	}

	template <class T>
	bool Line<T>::IsInside(const Vector2<T>& aPosition) const
	{
		Vector2<T> myDirection = aPosition - myPoint;
		if (myDirection.Dot(GetNormal()) <= 0)
		{
			return true;
		}
		else if (myDirection.Dot(GetNormal()) > 0)
		{
			return false;
		}
	}

	template <class T>
	const Vector2<T>& Line<T>::GetDirection() const
	{
		return myDirection;
	}

	template <class T>
	const Vector2<T> Line<T>::GetNormal() const
	{
		return Vector2<T>(-myDirection.y, myDirection.x).GetNormalized();
	}
}

namespace CU = CommonUtilities;
