#pragma once
#include <vector>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <class T>
	void Swap(T* aFirst, T* aSecond)
	{
		T value = *aFirst;
		*aFirst = *aSecond;
		*aSecond = value;
	}

	template <class T>
	int Parition(std::vector<T>& aVector, int aStartIndex, int aEndIndex)
	{
		int pivot = aVector[aEndIndex];
		int i = aStartIndex - 1;

		for (int j = aStartIndex; j < aEndIndex; ++j)
		{
			if (aVector[j] <= pivot)
			{
				++i;
				Swap(&aVector[i], &aVector[j]);
			}
		}
		Swap(&aVector[i + 1], &aVector[aEndIndex]);
		return i + 1;
	}

	template <class T>
	void SelectionSort(std::vector<T>& aVector)
	{
		for (int i = 0; i < aVector.size() - 1; i++)
		{
			int minIdx = i;
			for (int j = i + 1; j < aVector.size(); j++)
			{
				if (aVector[j] < aVector[minIdx])
				{
					minIdx = j;
				}
			}
			Swap(&aVector[minIdx], &aVector[i]);
		}
	}

	template <class T>
	void BubbleSort(std::vector<T>& aVector)
	{
		for (int i = 0; i < aVector.size() - 1; i++)
		{
			for (int j = 0; j < aVector.size() - i - 1; j++)
			{
				if (aVector[j] > aVector[j + 1])
				{
					Swap(&aVector[j], &aVector[j + 1]);
				}
			}
		}
	}

	template <class T>
	void QuickSort(std::vector<T>& aVector, int aStartIndex, int aEndIndex)
	{
		if (aStartIndex < aEndIndex)
		{
			const int pivot = Parition(aVector, aStartIndex, aEndIndex);

			QuickSort(aVector, aStartIndex, pivot - 1);
			QuickSort(aVector, pivot + 1, aEndIndex);
		}
	}

	template <class T>
	void QuickSort(std::vector<T>& aVector)
	{
		QuickSort(aVector, 0, aVector.size() - 1);
	}

	template <class T>
	void Merge(std::vector<T>& aVector, int aLeftLow, const int aLeftHigh, const int aRightLow,
			   const int aRightHigh)
	{
		int length = aRightHigh - aLeftLow + 1;
		std::vector<T> vector;
		for (int i = 0; i < length; ++i)
		{
			vector.push_back(aVector[i]);
		}
		int left = aLeftLow;
		int right = aRightLow;
		for (int i = 0; i < length; ++i)
		{
			if (left > aLeftHigh)
			{
				vector[i] = aVector[right++];
			}
			else if (right > aRightHigh)
			{
				vector[i] = aVector[left++];
			}
			else if (aVector[left] <= aVector[right])
			{
				vector[i] = aVector[left++];
			}
			else
			{
				vector[i] = aVector[right++];
			}
		}
		for (int i = 0; i < length; ++i)
		{
			aVector[aLeftLow++] = vector[i];
		}
	}

	template <class T>
	void MergeSort(std::vector<T>& aVector, int aLeftIndex, int aRightIndex)
	{
		if (aLeftIndex >= aRightIndex)
		{
			return;
		}
		int middle = (aLeftIndex + aRightIndex) / 2;
		MergeSort(aVector, aLeftIndex, middle);
		MergeSort(aVector, middle + 1, aRightIndex);
		Merge(aVector, aLeftIndex, middle, middle + 1, aRightIndex);
	}

	template <class T>
	void MergeSort(std::vector<T>& aVector)
	{
		MergeSort(aVector, 0, aVector.size() - 1);
	}
}
