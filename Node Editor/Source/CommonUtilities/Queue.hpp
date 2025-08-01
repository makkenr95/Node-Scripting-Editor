#pragma once
#include <assert.h>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <class T>
	class Queue
	{
	public:
		Queue();
		~Queue();
		int GetSize() const;
		const T& GetFront() const;
		T& GetFront();
		T GetValue(int aIndex) const;
		void Enqueue(const T& aValue);
		T Dequeue();
	private:
		bool CheckEmpty() const;
		bool CheckFull() const;
		void Resize();

		T* myQueue = new T[0];
		int myFirst;
		int myLast;
		int mySize = 0;
		int myArrayCapacity = 8;
	};

	template <class T>
	inline Queue<T>::Queue()
	{
		myFirst = -1;
		myLast = -1;
		T* queue = new T[myArrayCapacity];
		myQueue = queue;
	}

	template <class T>
	Queue<T>::~Queue()
	{
		delete[] myQueue;
		myQueue = nullptr;
	}

	template <class T>
	inline int Queue<T>::GetSize() const
	{
		return mySize;
	}

	template <class T>
	inline const T& Queue<T>::GetFront() const
	{
		assert(!CheckEmpty() && "Queue is empty");
		return myQueue[myFirst];
	}

	template <class T>
	inline T& Queue<T>::GetFront()
	{
		assert(!CheckEmpty() && "Queue is empty");
		return myQueue[myFirst];
	}

	template <class T>
	T Queue<T>::GetValue(int aIndex) const
	{
		return myQueue[aIndex];
	}

	template <class T>
	inline void Queue<T>::Enqueue(const T& aValue)
	{
		if (CheckFull())
		{
			Resize();
		}
		else if (CheckEmpty())
		{
			myFirst++;
		}
		myLast = (myLast + 1) % myArrayCapacity;
		myQueue[myLast] = aValue;
		mySize++;
	}

	template <class T>
	inline T Queue<T>::Dequeue()
	{
		assert(!CheckEmpty() && "Queue is empty");
		T queue = myQueue[myFirst];
		if (myFirst == myLast)
		{
			myFirst = -1;
			myLast = -1;
		}
		else
		{
			myFirst = (myFirst + 1) % myArrayCapacity;
		}
		mySize--;
		return queue;
	}

	template <class T>
	inline bool Queue<T>::CheckEmpty() const
	{
		return myFirst == -1;
	}

	template <class T>
	inline bool Queue<T>::CheckFull() const
	{
		return (myLast + 1) % myArrayCapacity == myFirst;
	}

	template <class T>
	inline void Queue<T>::Resize()
	{
		myArrayCapacity *= 2;
		T* queue = new T[myArrayCapacity];
		int i = 0;
		int tempFirst = myFirst;
		do
		{
			queue[i++] = myQueue[tempFirst];
			tempFirst = (tempFirst + 1) % (myArrayCapacity / 2);
		}
		while (tempFirst != myFirst);

		myFirst = 0;
		myLast = (myArrayCapacity / 2) - 1;
		myQueue = queue;
	}
}
