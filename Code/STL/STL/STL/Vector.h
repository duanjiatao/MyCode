#pragma once
#include<iostream>
#include<cassert>
using namespace std;

template <class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType* Iterator;
	typedef ValueType& Reference;

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	size_t Size()  //有效数据的个数
	{
		return _finish - _start;
	}

	size_t Capacity()  //容量
	{
		return _endOfStorage - _start;
	}

	Vector()
		: _start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	void _CheckCapacity()  //检查容量
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = size * 2 + 3;
			T* tmp = new T[capacity];

			if (_start)
			{
				memcpy(tmp, _start, sizeof(T)*size);
			}

			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + capacity;
		}
	}

	void PushBack(const T& x)
	{
		_CheckCapacity();
		assert(_finish != _endOfStorage);
		*_finish = x;
		++_finish;
	}

	void PopBack()
	{
		--_finish;
	}

	Iterator Erase(Iterator pos)
	{
		Iterator begin = pos + 1;
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		return pos;
	}

private:
	Iterator _start; //起始（有效数据）
	Iterator _finish; //末尾（最后一个有效数据的下一个位置）
	Iterator _endOfStorage; //容量末尾（最后位置的下一个位置）
};


void TestVector()
{
	Vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.PushBack(i);
	}


	Vector<int>::Iterator it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}