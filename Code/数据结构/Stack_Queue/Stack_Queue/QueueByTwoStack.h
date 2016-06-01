#pragma once
#include<iostream>
#include"Stack.h"
#include<stack>
using namespace std;

template<class T>
class QueueByStack
{
public:
	QueueByStack(const Stack<T>& s1, const Stack<T>& s2)
		:_s1(s1)  //拷贝构造
		, _s2(s2)
	{}

	QueueByStack(const QueueByStack<T>& q)
	{
		QueueByStack<T> tmp(q._s1, q._s2);
		this->_swap(tmp);
	}

	QueueByStack<T>& operator=(QueueByStack<T> q)
	{
		this->_swap(q);
		return *this;
	}


	~QueueByStack()
	{
		_s1.~Stack();
		_s2.~Stack();
	}

	void Push(const T& x)
	{
		_s1.Push(x);  //_s1只负责入栈
	}

	void Pop()
	{
		if (_s2.Empty())
		{
			while (!_s1.Empty())
			{
				T tmp = _s1.Top();
				_s2.Push(tmp);
				_s1.Pop();
			}
			_s2.Pop();
		}
		else
		{
			_s2.Pop();
		}
	}

	bool Empty(const Stack<T>& s)
	{
		return s.Empty();
	}

	T& Back()
	{
		if (_s1.Empty() && _s2.Empty())
		{
			exit(1);
		}
		else
		{
			if (_s1.Empty())
			{
				while (!_s2.Empty())
				{
					T tmp = _s2.Top();
					_s2.Pop();
					_s1.Push(tmp);
				}
			}
			return _s1.Top();
		}
	}

	T& Front()
	{
		if (_s1.Empty() && _s2.Empty())
		{
			exit(1);
		}
		else
		{
			if (_s2.Empty())
			{
				while (!_s1.Empty())
				{
					T tmp = _s1.Top();
					_s1.Pop();
					_s2.Push(tmp);
				}
			}
			return _s2.Top();
		}
	}

	void Diaplay()
	{
		_s1.Display();
		_s2.Display();
	}

protected:
	void _swap(QueueByStack<T>& q)
	{
		std::swap(_s1, q._s1);
		std::swap(_s2, q._s2);
	}

private:
	Stack<T> _s1;
	Stack<T> _s2;

};