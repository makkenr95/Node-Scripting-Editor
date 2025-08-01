#pragma once
#include <cassert>
#include <vector>

namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		Stack();
		int GetSize() const;
		const T& GetTop() const;
		T& GetTop();
		void Push(const T& aValue);
		T Pop();
	private:
		std::vector<T> myStack;
	};

	template <class T>
	Stack<T>::Stack()
	{
		std::vector<T> stack;
		myStack = stack;
	}

	template <class T>
	int Stack<T>::GetSize() const
	{
		myStack.max_size();
	}

	template <class T>
	const T& Stack<T>::GetTop() const
	{
		assert(!myStack.empty() && "Stack is empty");
		return myStack[myStack.back()];
	}

	template <class T>
	T& Stack<T>::GetTop()
	{
		assert(!myStack.empty() && "Stack is empty");
		return myStack[myStack.back()];
	}

	template <class T>
	void Stack<T>::Push(const T& aValue)
	{
		myStack.push_back(aValue);
	}

	template <class T>
	T Stack<T>::Pop()
	{
		assert(!myStack.empty() && "Stack is empty!");
		T lastElement = myStack.back();
		myStack.pop_back();
		return lastElement;
	}
}

namespace CU = CommonUtilities;
