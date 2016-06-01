#pragma once

#include<iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{}

	Stack(T* array, size_t size)
		:_array(new T[size])
		, _size(size)
		, _capacity(size)
	{
		for (size_t i = 0; i < _size; ++i)  //这里最好用for循环，不要用memcpy
		{
			_array[i] = array[i];
		}
	}

	~Stack()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

	void Display()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

	Stack(const Stack<T>& s)  //_capacity可能会不一样！
		:_array(NULL)
	{
		Stack<T> tmp(s._array, s._size);
		this->_swap(tmp);
	}

	Stack<T>& operator=(Stack<T> s)
	{
		_swap(s);
		return *this;
	}

protected:
	void _CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = 2 * _capacity + 3;
			T* array = new T[_capacity];
			for (size_t i = 0; i < _size; ++i)
			{
				array[i] = _array[i];
			}
			delete[] _array;
			_array = array;
		}
	}

	void _swap(Stack<T>& s)
	{
		std::swap(_array, s._array);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

public:
	void Push(const T& x)
	{
		_CheckCapacity();
		_array[_size++] = x;
	}

	void Pop()
	{
		assert(_size > 0);
		--_size;
	}

	bool Empty()
	{
		return (_size == 0);
	}

	size_t Size()
	{
		return _size;
	}

	T& Top()
	{
		return _array[_size - 1];
	}

private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

