#pragma once
#include "vector"

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <class T>
	class MinHeap
	{
	public:
		MinHeap(int* anArray, int aLength);
		MinHeap(const std::vector<int>& aVector);
		MinHeap();

		void Insert(int aValue);
		int GetMin();
		void DeleteMin();
	private:
		std::vector<int> myVector;
		void BubbleDown(int aIndex);
		void BubbleUp(int aIndex);
		void Heapify();
	};

	template <class T>
	::CommonUtilities::MinHeap<T>::MinHeap(int* anArray, int aLength)
	{
	}

	inline MinHeap::MinHeap(int* anArray, const int aLength) : myVector(aLength)
	{
		for (int i = 0; i < aLength; ++i)
		{
			myVector[i] = anArray[i];
		}
		Heapify();
	}

	inline MinHeap::MinHeap(const std::vector<int>& aVector) : myVector(aVector)
	{
		Heapify();
	}

	inline MinHeap::MinHeap()
	{
	}

	inline void MinHeap::Heapify()
	{
		const int length = myVector.size();
		for (int i = length - 1; i >= 0; --i)
		{
			BubbleDown(i);
		}
	}

	inline void MinHeap::BubbleDown(const int aIndex)
	{
		const int length = myVector.size();
		const int leftChildIndex = 2 * aIndex + 1;
		const int rightChildIndex = 2 * aIndex + 2;

		if (leftChildIndex >= length)
			return; //aIndex is a leaf

		int minIndex = aIndex;

		if (myVector[aIndex] > myVector[leftChildIndex])
		{
			minIndex = leftChildIndex;
		}

		if (rightChildIndex < length && myVector[minIndex] > myVector[rightChildIndex])
		{
			minIndex = rightChildIndex;
		}

		if (minIndex != aIndex)
		{
			//need to swap
			const int value = myVector[aIndex];
			myVector[aIndex] = myVector[minIndex];
			myVector[minIndex] = value;
			BubbleDown(minIndex);
		}
	}

	inline void MinHeap::BubbleUp(int aIndex)
	{
		if (aIndex == 0)
			return;

		const int parentIndex = (aIndex - 1) / 2;

		if (myVector[parentIndex] > myVector[aIndex])
		{
			const int value = myVector[parentIndex];
			myVector[parentIndex] = myVector[aIndex];
			myVector[aIndex] = value;
			BubbleUp(parentIndex);
		}
	}

	inline void MinHeap::Insert(int aValue)
	{
		const int length = myVector.size();
		myVector[length] = aValue;

		BubbleUp(length);
	}

	inline int MinHeap::GetMin()
	{
		return myVector[0];
	}

	inline void MinHeap::DeleteMin()
	{
		const int length = myVector.size();

		if (length == 0)
		{
			return;
		}

		myVector[0] = myVector[length - 1];
		myVector.pop_back();

		BubbleDown(0);
	}
}
