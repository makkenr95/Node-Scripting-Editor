#pragma once

#include "DoublyLinkedListNode.hpp"
#include "assert.h"

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		~DoublyLinkedList();
		int GetSize() const;

		DoublyLinkedListNode<T>* GetFirst()
		{
			return myHead;
		}

		DoublyLinkedListNode<T>* GetLast()
		{
			return myTail;
		}

		void InsertFirst(const T& aValue);
		void InsertLast(const T& aValue);
		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue);
		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue);
		void Remove(DoublyLinkedListNode<T>* aNode);
		DoublyLinkedListNode<T>* FindFirst(const T& aValue);
		DoublyLinkedListNode<T>* FindLast(const T& aValue);
		bool RemoveFirst(const T& aValue);
		bool RemoveLast(const T& aValue);

	private:
		DoublyLinkedListNode<T>* myHead;
		DoublyLinkedListNode<T>* myTail;
		int mySize;
	};

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList()
	{
		myHead = nullptr;
		myTail = nullptr;
		mySize = 0;
	}

	template <class T>
	DoublyLinkedList<T>::~DoublyLinkedList()
	{
		DoublyLinkedListNode<T>* node = myTail;
		while (node != nullptr)
		{
			DoublyLinkedListNode<T>* previous = node->GetPrevious();
			delete node;
			node = previous;
		}
	}

	template <class T>
	int DoublyLinkedList<T>::GetSize() const
	{
		return mySize;
	}

	template <class T>
	void DoublyLinkedList<T>::InsertFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
		if (mySize > 0)
		{
			myHead->myPrevious = node;
			node->myNext = myHead;
		}
		else
		{
			myTail = node;
		}
		myHead = node;
		mySize++;
	}

	template <class T>
	void DoublyLinkedList<T>::InsertLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
		if (mySize > 0)
		{
			myTail->myNext = node;
			node->myPrevious = myTail;
		}
		else
		{
			myHead = node;
		}
		myTail = node;
		mySize++;
	}

	template <class T>
	void DoublyLinkedList<T>::InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		assert(mySize > 0 && "List is empty");
		assert(aNode != nullptr && "Argument aNode is nullptr");

		if (aNode == myHead)
		{
			InsertFirst(aValue);
			return;
		}

		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		DoublyLinkedListNode<T>* currentNode = myHead;

		while (currentNode != nullptr)
		{
			if (aNode == currentNode)
			{
				newNode->myNext = aNode;
				newNode->myPrevious = aNode->myPrevious;

				aNode->myPrevious->myNext = newNode;
				aNode->myPrevious = newNode;
				mySize++;
				return;
			}
			currentNode = currentNode->myNext;
		}
		assert(currentNode != nullptr && "Node not found");
	}

	template <class T>
	void DoublyLinkedList<T>::InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		assert(mySize > 0 && "List is empty");
		assert(aNode != nullptr && "Argument aNode is nullptr");

		if (aNode == myTail)
		{
			InsertLast(aValue);
			return;
		}

		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		DoublyLinkedListNode<T>* currentNode = myHead;

		while (currentNode != nullptr)
		{
			if (aNode == currentNode)
			{
				currentNode->myNext->myPrevious = newNode;
				newNode->myNext = currentNode->myNext;
				aNode->myNext = newNode;
				newNode->myPrevious = aNode;
				mySize++;
				return;
			}
			currentNode = currentNode->myNext;
		}
		assert(currentNode != nullptr && "Node not found");
	}

	template <class T>
	void DoublyLinkedList<T>::Remove(DoublyLinkedListNode<T>* aNode)
	{
		assert(aNode != nullptr && "Argument aNode is nullptr");
		DoublyLinkedListNode<T>* currentNode = myHead;
		while (currentNode != nullptr)
		{
			if (currentNode == aNode)
			{
				DoublyLinkedListNode<T>* prev = currentNode->myPrevious;
				DoublyLinkedListNode<T>* next = currentNode->myNext;
				if (prev != nullptr)
				{
					prev->myNext = next;
					if (currentNode == myTail)
					{
						myTail = prev;
					}
				}
				if (next != nullptr)
				{
					next->myPrevious = prev;
					if (currentNode == myHead)
					{
						myHead = next;
					}
				}
				mySize--;
				delete currentNode;
				if (mySize == 0)
				{
					myHead = nullptr;
					myTail = nullptr;
				}
				return;
			}
			currentNode = currentNode->myNext;
		}
	}

	template <class T>
	DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myHead;
		while (node != nullptr)
		{
			if (node->myData == aValue)
			{
				return node;
			}
			node = node->GetNext();
		}
		return nullptr;
	}

	template <class T>
	DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = myTail;
		while (node != nullptr)
		{
			if (node->myData == aValue)
			{
				return node;
			}
			node = node->GetPrevious();
		}
		return nullptr;
	}

	template <class T>
	bool DoublyLinkedList<T>::RemoveFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = FindFirst(aValue);
		if (node != nullptr)
		{
			Remove(node);
			return true;
		}
		return false;
	}

	template <class T>
	bool DoublyLinkedList<T>::RemoveLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* node = FindLast(aValue);
		if (node != nullptr)
		{
			Remove(node);
			return true;
		}
		return false;
	}
};

namespace CU = CommonUtilities;
