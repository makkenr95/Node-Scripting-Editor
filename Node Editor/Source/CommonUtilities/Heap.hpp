#pragma once
#include <vector>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <class T>
	class Heap
	{
	public:
		int GetSize() const;
		void Enqueue(const T& aElement);
		const T& GetTop() const;
		T Dequeue();

	private:
		std::vector<T> myHeap;
	};

	template <class T>
	inline int Heap<T>::GetSize() const
	{
		return myHeap.size();
	}

	template <class T>
	inline void Heap<T>::Enqueue(const T& aElement)
	{
		myHeap.push_back(aElement);
		if (myHeap.size() < 2)
		{
			return;
		}

		int currentIndex = myHeap.size() - 1;
		while (myHeap[(currentIndex - 1) / 2] < myHeap[currentIndex])
		{
			std::swap(myHeap[currentIndex], myHeap[(currentIndex - 1) / 2]);
			currentIndex = (currentIndex - 1) / 2;
			if (currentIndex < 1)
			{
				break;
			}
		}
	}

	template <class T>
	inline const T& Heap<T>::GetTop() const
	{
		return myHeap[0];
	}

	template <class T>
	inline T Heap<T>::Dequeue()
	{
		T value = myHeap[0];

		myHeap[0] = myHeap.back();

		int currentIndex = 0;
		while (myHeap[currentIndex] < myHeap[2 * currentIndex + 1] || myHeap[currentIndex] < myHeap[2 * currentIndex +
			2])
		{
			if (myHeap[2 * currentIndex + 1] < myHeap[2 * currentIndex + 2])
			{
				std::swap(myHeap[currentIndex], myHeap[2 * currentIndex + 2]);
				currentIndex = 2 * currentIndex + 2;
			}
			else
			{
				std::swap(myHeap[currentIndex], myHeap[2 * currentIndex + 1]);
				currentIndex = 2 * currentIndex + 1;
			}
			if (currentIndex < ((myHeap.size() - 1) / 2) + 1)
			{
				break;
			}
		}

		myHeap.pop_back();
		return value;
	}
}
