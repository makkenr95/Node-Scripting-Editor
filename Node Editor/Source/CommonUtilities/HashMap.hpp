#pragma once
#include <cstdint>
#include <system_error>
#include "HashNode.hpp"

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <class Key, class Value>
	class HashMap
	{
	public:
		HashMap(const int aCapacity);
		~HashMap();
		bool Insert(const Key& aKey, const Value& aValue);
		bool Remove(const Key& aKey);
		const Value* Get(const Key& aKey) const;
		Value* Get(const Key& aKey);

		uint32_t Hash(const Key& aKey)
		{
			return std::hash<Key>{}(aKey);
		}

	private:
		HashNode<uint32_t, Value>* myNodes = new HashNode<uint32_t, Value>[0];
		int myCount = 0;
		int myCapacity = 0;
	};

	template <class Key, class Value>
	HashMap<Key, Value>::HashMap(const int aCapacity)
	{
		myNodes = new HashNode<uint32_t, Value>[aCapacity];
		myCount = 0;
		myCapacity = aCapacity;
	}

	template <class Key, class Value>
	HashMap<Key, Value>::~HashMap()
	{
		delete[] myNodes;
		myNodes = nullptr;
	}

	template <class Key, class Value>
	bool HashMap<Key, Value>::Insert(const Key& aKey, const Value& aValue)
	{
		if (myCount < myCapacity)
		{
			int index = myCount;
			for (int i = 0; i < myCount; ++i)
			{
				if (*myNodes[i].GetKey() == Hash(aKey))
				{
					index = i;
					break;
				}
			}
			myNodes[index] = HashNode<uint32_t, Value>(Hash(aKey), aValue);
			if (index == myCount)
			{
				myCount++;
			}
			return true;
		}
		return false;
	}

	template <class Key, class Value>
	bool HashMap<Key, Value>::Remove(const Key& aKey)
	{
		for (int i = 0; i < myCount; ++i)
		{
			if (*myNodes[i].GetKey() == Hash(aKey))
			{
				myNodes[i] = myNodes[myCount - 1];
				// myNodes[i].SetValue(myNodes[myCount - 1].GetValue());
				// myNodes[i].SetKey(myNodes[myCount - 1].GetKey());
				myCount--;
				return true;
			}
		}
		return false;
	}

	template <class Key, class Value>
	const Value* HashMap<Key, Value>::Get(const Key& aKey) const
	{
		for (int i = 0; i < myCount; ++i)
		{
			if (*myNodes[i].GetKey() == Hash(aKey))
			{
				return myNodes[i].GetValue();
			}
		}
		return nullptr;
	}

	template <class Key, class Value>
	Value* HashMap<Key, Value>::Get(const Key& aKey)
	{
		for (int i = 0; i < myCount; ++i)
		{
			if (*myNodes[i].GetKey() == Hash(aKey))
			{
				return myNodes[i].GetValue();
			}
		}
		return nullptr;
	}
}
