#pragma once
#include "BSTNode.hpp"

namespace CommonUtilities
{
	template <class T>
	class BSTSet
	{
	public:
		BSTSet();
		~BSTSet();
		bool HasElement(const T& aValue);
		void Insert(const T& aValue);
		void Remove(const T& aValue);
		void MakeEmpty(BSTNode<T>*& aNode);

		BSTNode<T>* RotateRight(BSTNode<T>* aGrandParent, BSTNode<T>* aParent, BSTNode<T>* aLeftChild);
		void RotateLeft(BSTNode<T>* aGrandParent, BSTNode<T>* aParent, BSTNode<T>* aRightChild);
		int MSB(int aN);
		int GreatestPowerOf2LessThanN(int aN);
		void CreatePerfectBST();
		void MakeRotations(int aBound);
		void CreateBackbone();
		void DSWBalance();

		BSTNode<T>* FindMin(BSTNode<T>* aNode);
		BSTNode<T>* FindMax(BSTNode<T>* aNode);
	private:
		bool HasElement(const T& aValue, BSTNode<T>* aNode);
		void Insert(const T& aValue, BSTNode<T>*& aNode);
		void Remove(const T& aValue, BSTNode<T>*& aNode);
		BSTNode<T>* myRoot;
	};

	template <class T>
	BSTSet<T>::BSTSet()
	{
		myRoot = nullptr;
	}

	template <class T>
	BSTSet<T>::~BSTSet()
	{
		MakeEmpty(myRoot);
	}

	template <class T>
	bool BSTSet<T>::HasElement(const T& aValue)
	{
		if (myRoot == nullptr)
		{
			return false;
		}

		return HasElement(aValue, myRoot);
	}

	template <class T>
	bool BSTSet<T>::HasElement(const T& aValue, BSTNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return false;
		}
		if (aValue < aNode->myData)
		{
			return HasElement(aValue, aNode->myLeft);
		}
		if (aNode->myData < aValue)
		{
			return HasElement(aValue, aNode->myRight);
		}
		return true;
	}

	template <class T>
	void BSTSet<T>::Insert(const T& aValue)
	{
		if (HasElement(aValue))
		{
			return;
		}

		Insert(aValue, myRoot);
	}

	template <class T>
	void BSTSet<T>::Insert(const T& aValue, BSTNode<T>*& aNode)
	{
		if (aNode == nullptr)
		{
			aNode = new BSTNode<T>{aValue};
		}
		else if (aValue < aNode->myData)
		{
			Insert(aValue, aNode->myLeft);
		}
		else if (aNode->myData < aValue)
		{
			Insert(aValue, aNode->myRight);
		}
	}

	template <class T>
	void BSTSet<T>::Remove(const T& aValue)
	{
		if (myRoot == nullptr)
		{
			return;
		}

		Remove(aValue, myRoot);
	}

	template <class T>
	void BSTSet<T>::Remove(const T& aValue, BSTNode<T>*& aNode)
	{
		if (aNode == nullptr)
		{
			return;
		}
		if (aValue < aNode->myData)
		{
			Remove(aValue, aNode->myLeft);
		}
		else if (aNode->myData < aValue)
		{
			Remove(aValue, aNode->myRight);
		}
		else if (aNode->myLeft != nullptr && aNode->myRight != nullptr)
		{
			aNode->myData = FindMin(aNode->myRight)->myData;
			Remove(aNode->myData, aNode->myRight);
		}
		else
		{
			aNode = (aNode->myLeft != nullptr) ? aNode->myLeft : aNode->myRight;
		}
	}

	template <class T>
	void BSTSet<T>::MakeEmpty(BSTNode<T>*& aNode)
	{
		if (aNode != nullptr)
		{
			MakeEmpty(aNode->myLeft);
			MakeEmpty(aNode->myRight);
			delete aNode;
		}
		aNode = nullptr;
	}

	template <class T>
	BSTNode<T>* BSTSet<T>::RotateRight(BSTNode<T>* aGrandParent, BSTNode<T>* aParent, BSTNode<T>* aLeftChild)
	{
		if (aGrandParent != nullptr)
		{
			aGrandParent->myRight = aLeftChild;
		}
		else
		{
			myRoot = aLeftChild;
		}
		aParent->myLeft = aLeftChild->myRight;
		aLeftChild->myRight = aParent;
		return aGrandParent;
	}

	template <class T>
	void BSTSet<T>::RotateLeft(BSTNode<T>* aGrandParent, BSTNode<T>* aParent, BSTNode<T>* aRightChild)
	{
		if (aGrandParent != nullptr)
		{
			aGrandParent->myRight = aRightChild;
		}
		else
		{
			myRoot = aRightChild;
		}
		aParent->myRight = aRightChild->myLeft;
		aRightChild->myLeft = aParent;
	}

	template <class T>
	int BSTSet<T>::MSB(int aN)
	{
		int ndx = 0;
		while (1 < aN)
		{
			aN = (aN >> 1);
			ndx++;
		}
		return ndx;
	}

	template <class T>
	int BSTSet<T>::GreatestPowerOf2LessThanN(const int aN)
	{
		const int x = MSB(aN);
		return (1 << x);
	}

	template <class T>
	void BSTSet<T>::CreatePerfectBST()
	{
		int n = 0;
		for (BSTNode<T>* node = myRoot; node != nullptr; node = node->myRight)
		{
			n++;
		}
		int m = GreatestPowerOf2LessThanN(n + 1) - 1;
		MakeRotations(n - m);
		while (m > 1)
		{
			MakeRotations(m /= 2);
		}
	}

	template <class T>
	void BSTSet<T>::MakeRotations(int aBound)
	{
		BSTNode<T>* grandParent = nullptr;
		BSTNode<T>* parent = myRoot;
		BSTNode<T>* child = myRoot->myRight;

		for (; aBound > 0; aBound--)
		{
			if (child != nullptr)
			{
				RotateLeft(grandParent, parent, child);
				grandParent = child;
				parent = grandParent->myRight;
				child = parent->myRight;
			}
			else
			{
				break;
			}
		}
	}

	template <class T>
	void BSTSet<T>::CreateBackbone()
	{
		BSTNode<T>* grandParent = nullptr;
		BSTNode<T>* parent = myRoot;
		BSTNode<T>* leftChild;

		while (nullptr != parent)
		{
			leftChild = parent->myLeft;
			if (nullptr != leftChild)
			{
				grandParent = RotateRight(grandParent, parent, leftChild);
				parent = leftChild;
			}
			else
			{
				grandParent = parent;
				parent = parent->myRight;
			}
		}
	}

	template <class T>
	void BSTSet<T>::DSWBalance()
	{
		if (myRoot != nullptr)
		{
			CreateBackbone();
			CreatePerfectBST();
		}
	}

	template <class T>
	BSTNode<T>* BSTSet<T>::FindMin(BSTNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return nullptr;
		}
		if (aNode->GetLeft() == nullptr())
		{
			return aNode;
		}
		return FindMin(aNode->GetLeft());
	}

	template <class T>
	BSTNode<T>* BSTSet<T>::FindMax(BSTNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return nullptr;
		}
		if (aNode->GetRight() == nullptr())
		{
			return aNode;
		}
		return FindMax(aNode->GetRight());
	}
}

namespace CU = CommonUtilities;
