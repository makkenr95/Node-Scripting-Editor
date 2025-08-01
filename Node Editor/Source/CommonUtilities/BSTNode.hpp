#pragma once

namespace CommonUtilities
{
	template <class T>
	class BSTSet;

	template <class T>
	class BSTNode
	{
	public:
		BSTNode<T>(const BSTSet<T>&) = delete;
		BSTNode<T>& operator=(const BSTSet<T>&) = delete;
		const T& GetValue() const;
		T& GetValue();
		BSTNode<T>* GetLeft() const;
		BSTNode<T>* GetRight() const;
	private:
		friend class BSTSet<T>;
		BSTNode(const T& aValue);
		~BSTNode();

		T myData;
		BSTNode<T>* myLeft = nullptr;
		BSTNode<T>* myRight = nullptr;
	};

	template <class T>
	inline const T& BSTNode<T>::GetValue() const
	{
		return myData;
	}

	template <class T>
	inline T& BSTNode<T>::GetValue()
	{
		return myData;
	}

	template <class T>
	inline BSTNode<T>* BSTNode<T>::GetLeft() const
	{
		return myLeft;
	}

	template <class T>
	inline BSTNode<T>* BSTNode<T>::GetRight() const
	{
		return myRight;
	}

	template <class T>
	BSTNode<T>::BSTNode(const T& aValue)
	{
		myData = aValue;
	}

	template <class T>
	BSTNode<T>::~BSTNode()
	{
		delete myRight;
		myRight = nullptr;
		delete myLeft;
		myLeft = nullptr;
	}
}
