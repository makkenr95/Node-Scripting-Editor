#pragma once
#include "Vector2.hpp"
#include <vector>
#include "Line.hpp"

namespace CommonUtilities
{
	template <class T>
	class LineVolume
	{
	public:
		LineVolume() = default;
		LineVolume(const std::vector<Line<T>>& aLineList);
		void AddLine(const Line<T>& aLine);
		bool IsInside(const Vector2<T>& aPosition);
	private:
		std::vector<Line<T>> myLines;
	};

	template <class T>
	LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLines = aLineList;
	}

	template <class T>
	void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLines.push_back(aLine);
	}

	template <class T>
	bool LineVolume<T>::IsInside(const Vector2<T>& aPosition)
	{
		for (size_t i = 0; i < myLines.size(); i++)
		{
			if (myLines[i].IsInside(aPosition) == false)
			{
				return false;
			}
		}
		return true;
	}
}

namespace CU = CommonUtilities;
