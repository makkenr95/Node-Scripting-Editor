#pragma once

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList;

	template <class T>
	class DoublyLinkedListNode
	{
	public:
		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T>&) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T>&) = delete;
		const T& GetValue() const;
		T& GetValue();
		DoublyLinkedListNode<T>* GetNext() const;
		DoublyLinkedListNode<T>* GetPrevious() const;
	private:
		friend class DoublyLinkedList<T>;
		DoublyLinkedListNode(const T& aValue);
		~DoublyLinkedListNode();

		T myData;
		DoublyLinkedListNode<T>* myPrevious = nullptr;
		DoublyLinkedListNode<T>* myNext = nullptr;
	};

	template <class T>
	const T& DoublyLinkedListNode<T>::GetValue() const
	{
		return myData;
	}

	template <class T>
	T& DoublyLinkedListNode<T>::GetValue()
	{
		return myData;
	}

	template <class T>
	DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetNext() const
	{
		return myNext;
	}

	template <class T>
	DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetPrevious() const
	{
		return myPrevious;
	}

	template <class T>
	DoublyLinkedListNode<T>::DoublyLinkedListNode(const T& aValue)
	{
		myData = aValue;
	}

	template <class T>
	DoublyLinkedListNode<T>::~DoublyLinkedListNode()
	{
		myNext = nullptr;
		myPrevious = nullptr;
	}
}
