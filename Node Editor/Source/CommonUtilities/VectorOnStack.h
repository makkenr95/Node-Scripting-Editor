#pragma once
#include <cassert>
#include <initializer_list>
#include <array>

namespace CommonUtilities
{
	template <typename Type, int size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aInitList);
		~VectorOnStack();
		VectorOnStack& operator=(const VectorOnStack& aVectorOnStack);
		inline const Type& operator[](const CountType aIndex) const;
		inline Type& operator[](const CountType aIndex);
		inline void Add(const Type& aObject);
		inline void Insert(const CountType aIndex, const Type& aObject);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(const CountType aIndex);
		inline void Clear();
		inline CountType Size() const;

	private:
		//Type* myData;
		CountType myCurrentSize = 0;
		std::array<Type, size> myData;
		bool mySafeMode = UseSafeModeFlag;
	};

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		myCurrentSize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		if (UseSafeModeFlag == true)
		{
			*this = aVectorOnStack;
		}
		else
		{
			memcpy(&myData, &aVectorOnStack.myData, sizeof(Type) * aVectorOnStack.myCurrentSize);
			memcpy(&myCurrentSize, &aVectorOnStack.myCurrentSize, sizeof(aVectorOnStack.myCurrentSize));
			memcpy(&mySafeMode, &aVectorOnStack.mySafeMode, sizeof(bool));
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aInitList)
	{
		assert(static_cast<size_t>(size) >= aInitList.size());
		myCurrentSize = 0;
		mySafeMode = UseSafeModeFlag;

		Clear();
		for (auto v : aInitList)
		{
			Add(v);
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, size, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		//myData = new Type[size];
		myCurrentSize = 0;
		mySafeMode = UseSafeModeFlag;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, size, CountType, UseSafeModeFlag>& VectorOnStack<
		Type, size, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		if (mySafeMode)
		{
			mySafeMode = aVectorOnStack.mySafeMode;
			myCurrentSize = aVectorOnStack.myCurrentSize;
			myData = aVectorOnStack.myData;
		}
		else
		{
			memcpy(&myData, &aVectorOnStack.myData, sizeof(Type) * aVectorOnStack.myCurrentSize);
			memcpy(&myCurrentSize, &aVectorOnStack.myCurrentSize, sizeof(aVectorOnStack.myCurrentSize));
			memcpy(&mySafeMode, &aVectorOnStack.mySafeMode, sizeof(bool));
		}

		return *this;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	const Type& VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType aIndex) const
	{
		assert(aIndex >= 0 && aIndex < myCurrentSize);
		return myData[aIndex];
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	Type& VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType aIndex)
	{
		assert(aIndex >= 0 && aIndex < myCurrentSize);
		return myData[aIndex];
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(myCurrentSize < size);
		myData[myCurrentSize] = aObject;
		++myCurrentSize;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Insert(const CountType aIndex, const Type& aObject)
	{
		assert(myCurrentSize < size);
		assert(aIndex >= 0 && aIndex <= myCurrentSize);
		assert(myCurrentSize + 1 <= size);
		++myCurrentSize;

		if (mySafeMode)
		{
			for (CountType index = size - 2; index >= aIndex; --index)
			{
				myData[index + 1] = myData[index];
			}
			myData[aIndex] = aObject;
		}
		else
		{
			memcpy(&myData[aIndex] + 1, &myData[aIndex], sizeof(Type) * (myCurrentSize - aIndex));
			memcpy(&myData[aIndex], &aObject, sizeof(Type));
		}
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		assert(myCurrentSize >= 1);
		for (CountType index = 0; index < size; index++)
		{
			if (myData[index] == aObject)
			{
				myData[index] = myData[myCurrentSize - 1];
				break;
				//--myCurrentSize;
			}
		}
		--myCurrentSize;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(const CountType aIndex)
	{
		assert(aIndex < myCurrentSize&& aIndex >= 0);
		myData[aIndex] = myData[myCurrentSize - 1];
		--myCurrentSize;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Clear()
	{
		myCurrentSize = 0;
	}

	template <typename Type, int size, typename CountType, bool UseSafeModeFlag>
	CountType VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Size() const
	{
		return myCurrentSize;
	}
}
