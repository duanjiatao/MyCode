#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}

	BitMap(size_t size)
		:_size(0)
	{
		_array.resize((size >> 5) + 1);
	}

	~BitMap()
	{
		_size = 0;
	}

	bool Set(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		if (_array[index] & (1 << n))
			return false;

		_array[index] |= (1 << n);
		++_size;
		return true;
	}

	bool Reset(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		if (_array[index] & (1 << n))
		{
			_array[index] &= (~(1 << n));
			--_size;
			return true;
		}
		return false;
	}

	bool Test(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		return _array[index] & (1 << n);
	}

	void Clear()
	{
		_array.assign(_array.size(), 0);
		_size = 0;
	}

private:
	vector<size_t> _array;
	size_t _size;

};

void Test1()
{
	BitMap bt(65);

	bt.Set(1);
	bt.Set(4);
	bt.Set(33);
	bt.Reset(33);
	bt.Clear();
}

void Test2()
{
	BitMap bt(-1);

	bt.Set(1);
	bt.Clear();
}
