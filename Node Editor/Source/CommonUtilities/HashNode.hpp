#pragma once

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	template <typename Key, typename Value>
	class HashNode
	{
	public:
		HashNode(const Key& aKey, const Value& aValue);
		HashNode() = default;
		Key* GetKey() const;
		Value* GetValue() const;
		//void SetValue(Value* aValue);
		//void SetKey(Key* aKey);

	private:
		Key* myKey;
		Value* myValue;
	};

	template <typename Key, typename Value>
	HashNode<Key, Value>::HashNode(const Key& aKey, const Value& aValue)
	{
		myValue = new Value(aValue);
		myKey = new Key(aKey);
	}

	template <typename Key, typename Value>
	Key* HashNode<Key, Value>::GetKey() const
	{
		return myKey;
	}

	template <typename Key, typename Value>
	Value* HashNode<Key, Value>::GetValue() const
	{
		return myValue;
	}

	//template <typename Key, typename Value>
	//void HashNode<Key, Value>::SetValue(Value* aValue)
	//{
	//	myValue = aValue;
	//}
	//
	//template <typename Key, typename Value>
	//void HashNode<Key, Value>::SetKey(Key* aKey)
	//{
	//	myKey = aKey;
	//}
}
