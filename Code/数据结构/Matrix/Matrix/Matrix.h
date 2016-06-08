#pragma once
#include<iostream>
#include<cassert>
#include<vector>
using namespace std;


template<class T>
class SymmetricMatrix  //对称矩阵的压缩存储
{
public:
	SymmetricMatrix(const T* a, size_t n)
		:_array(new T[n*(n+1)/2])
		, _n(n)
	{
		for (size_t i = 0; i < _n; ++i)
		{
			for (size_t j = 0; j < _n; ++j)
			{
				if (i >= j)
				{
					_array[i*(i+1)/2 + j] = a[i*_n + j];
				}
				else
				{
					break;
				}
			}
		}
	}

	~SymmetricMatrix()
	{
		if (_array)
			delete[] _array;
	}

	T& AccessNum(size_t i, size_t j)
	{
		assert(i < _n && j < _n);

		if (i < j)
		{
			std::swap(i, j);
		}
		return _array[i*(i + 1) / 2 + j];
	}

	void Display()
	{
		for (size_t i = 0; i < _n; ++i)
		{
			for (size_t j = 0; j < _n; ++j)
			{
				if (i < j)
				{
					cout << _array[j*(j + 1) / 2 + i] << " ";
				}
				else
				{
					cout << _array[i*(i + 1) / 2 + j] << " ";
				}
			}
			cout << endl;
		}
	}

private:
	T* _array;
	size_t _n;
};


template<class T>
struct Trituple
{
	size_t _row;
	size_t _col;
	int _value;
};

template<class T>
class SparseMatrix  //系稀疏矩阵及其快速转置
{
public:
	SparseMatrix()
		:_colSize(0)
		, _rowSize(0)
	{}

	SparseMatrix(const T* a, const size_t row, const size_t col, const T invalid)
		:_rowSize(row)
		, _colSize(col)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < _rowSize; ++i)
		{
			for (size_t j = 0; j < _colSize; ++j)
			{
				T tmp = a[i*_colSize + j];
				if (tmp != _invalid)
				{
					Trituple<T> t;
					t._row = i;
					t._col = j;
					t._value = tmp;
					_array.push_back(t);
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; ++i)
		{
			for (size_t j = 0; j < _colSize; ++j)
			{
				if (index < _array.size() &&
					_array[index]._row == i &&
					_array[index]._col == j)
				{
					cout << _array[index++]._value << " ";
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
	}

	SparseMatrix<T> FastTranspose()  //快速转置
	{
		SparseMatrix<int> smT;  //转置后的矩阵
		smT._rowSize = _colSize;
		smT._colSize = _rowSize;
		smT._invalid = _invalid;

		int* rowCounts = new int[_colSize];  //转置后每行的有效数据个数
		int* rowStart = new int[_colSize];  //转置后每行的起始位置
		memset(rowCounts, 0, sizeof(int)*_colSize);  //置0
		memset(rowStart, 0, sizeof(int)*_colSize);  //置0

		for (size_t i = 0; i < _array.size(); ++i)
		{
			++rowCounts[_array[i]._col];
		}

		rowStart[0] = 0;
		for (size_t i = 1; i < _colSize; ++i)
		{
			rowStart[i] = rowStart[i - 1] + rowCounts[i - 1];
		}

		smT._array.resize(_array.size());
		for (size_t index = 0; index < _array.size(); ++index)
		{
			size_t begin = rowStart[_array[index]._col];
			Trituple<T> tmp;
			tmp._row = _array[index]._col;
			tmp._col = _array[index]._row;
			tmp._value = _array[index]._value;

			smT._array[begin] = tmp;
			++rowStart[_array[index]._col];
		}

		delete[] rowCounts;  rowCounts = NULL;
		delete[] rowStart;  rowStart = NULL; 

		return smT;
	}

private:
	vector<Trituple<T>> _array;
	size_t _rowSize;
	size_t _colSize;
	T _invalid;
};



void Test1()  //测试对称矩阵
{
	int a[5][5] =  //对称矩阵一定是方阵
	{
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 },
	};

	SymmetricMatrix<int> sm((int*)a, 5);
	sm.Display();
	cout << sm.AccessNum(1, 4) << endl;
}

void Test2()  //测试稀疏矩阵及其快速转置
{
	int a[6][5] =
	{
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 2, 0, 4, 0, 6 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
	};

	SparseMatrix<int> sm1((int*)a, 6, 5, 0);
	sm1.Display();

	SparseMatrix<int> sm2 = sm1.FastTranspose();
	cout << endl;
	sm2.Display();
}

