#pragma once
#include<assert.h>


typedef int DataType;

class SeqList
{
public:

	SeqList()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{}

	SeqList(DataType* array, size_t size)
		:_array(new DataType[size])
		,_size(size)
		, _capacity(size)
	{
		memcpy(_array, array, sizeof(DataType)*size);
	}
	
	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
		}
		//cout << "~SeqList()" << endl;
	}

	void _Swap(SeqList& s)
	{
		DataType* array_tmp = _array;
		_array = s._array;
		s._array = array_tmp;

		size_t size_tmp = _size;
		_size = s._size;
		s._size = size_tmp;

		size_t capacity_tmp = _capacity;
		_capacity = s._capacity;
		s._capacity = capacity_tmp;

	}

	SeqList(const SeqList& s)
		:_array(NULL)
		, _size(s._size)
		, _capacity(s._capacity)
	{
		SeqList tmp(s._array,s._size);
		_Swap(tmp);

	}

	SeqList& operator=(SeqList s)
	{
		_Swap(s);
		return *this;
	}

	//SeqList& operator=(SeqList& s)
	//{
	//	//_Swap(s);
	//	delete[] _array;
	//	DataType* tmp = new DataType[s._size];
	//	memcpy(tmp, s._array, sizeof(DataType)*s._size);

	//	_array = tmp;
	//	_size = s._size;
	//	_capacity = s._capacity;

	//	return *this;
	//}

	void Print()
	{
		for (size_t i = 0; i < _size; i++)
		{
			cout << _array[i] << " ";
		}

		cout << endl;
	}

	void PushBack(const DataType& x)
	{
		_CheckCapacity();
		_array[_size++] = x;
	}

	void PushFront(const DataType& x)
	{
		_CheckCapacity();
		for (int i = _size - 1; i >= 0; --i)
		{
			_array[i + 1] = _array[i];
		}
		_array[0] = x;
		++_size;
	}

	void PopBack()
	{
		if (_size == 0)
		{
			cout << "SeqList is Empty" << endl;
			return;
		}
		--_size;
	}

	void PopFront()
	{
		if (_size == 0)
		{
			cout << "SeqList is Empty" << endl;
			return;
		}
		for (size_t i = 0; i < _size-1; ++i)
		{
			_array[i] = _array[i + 1];
		}
		--_size;
	}

	void Insert(size_t pos, const DataType& x)
	{
		assert(pos <= _size);
		_CheckCapacity();
		if (pos == _size) //相当于尾插
		{
			PushBack(x);
		}
		else if (pos == 0)
		{
			PushFront(x);
		}
		else
		{
			for (size_t i = _size-1; i >= pos; --i)
			{
				_array[i + 1] = _array[i];
			}
			_array[pos] = x;
		}

		++_size;
	}

	void Erase(size_t pos)
	{
		assert(pos < _size);
		if (_size == 0)
		{
			cout << "SeqList is Empty" << endl;
			return;
		}
		for (size_t i = pos; i < _size-1; ++i)
		{
			_array[i] = _array[i + 1];
		}

		--_size;
	}


	int Find(const DataType& x)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == x)
			{
				return i;
			}
		}

		return -1;
	}
	

	DataType& operator[](size_t index)
	{
		if (index < _size)
		{
			return _array[index];
		}
		cout << "Not found" << endl;
	}

	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}

	void Clear()  //不释放空间
	{
		SeqList tmp;  //构造一个空表
		_Swap(tmp);   //交换，释放局部变量
	}

	//void Reserve(size_t size);  //保留空间，增容

private:
	void _CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(DataType)*_size);
			delete[] _array;

			_array = tmp;
		}
	}

private:
	DataType* _array;
	size_t _size;
	size_t _capacity;
};

