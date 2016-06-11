#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Less
{
	bool operator()(const T& num1, const T& num2)
	{
		return num1 < num2;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& num1, const T& num2)
	{
		return num1 > num2;
	}
};


template<class T,class cmp = Less<T>>
class Heap
{
public:
	Heap()
	: _size(0)
	{}

	Heap(const T* a, size_t size)
		: _size(size)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_hp.push_back(a[i]);
		}
	}

	void CreatHeap()  // 建 大/小 堆
	{
		for (int i = (_size-2)/2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}

	void Pop()  //删除 堆顶
	{
		if (_size == 0)
			return;

		std::swap(_hp[0], _hp[_size - 1]);
		--_size;
		_hp.pop_back();
		AdjustDown(0);  //向下调整
	}

	void Push(const T& x)  //插到 堆尾
	{
		_hp.push_back(x);
		++_size;
		AdjustUp(_size - 1);  //向上调整
	}

	T& Top()  //取 堆顶
	{
		if (_size > 0)
			return _hp[0];
	}

	bool Empty()  //堆 判空
	{
		return _size == 0;
	}

	

protected:

	void AdjustDown(size_t root)
	{
		size_t child = root * 2 + 1;  //计算左孩子

		while (child < _size)
		{
			if (child + 1 < _size && cmp()(_hp[child + 1], _hp[child]))
			{
				++child;
			}
			if (cmp()(_hp[child], _hp[root]))  //第一次这里出错！注意参数前后顺序！
			{
				std::swap(_hp[root], _hp[child]);
				root = child;
				child = root * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustUp(size_t root)
	{
		size_t parent = (root - 1) / 2;  //计算父节点

		while (parent > 0)  //注意这里条件，否则可能会导致死循环！
		{
			if (cmp()(_hp[root], _hp[parent]))  //注意这里参数的顺序！
			{
				std::swap(_hp[root], _hp[parent]);
				root = parent;
				parent = (root - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	//void AdjustDown(vector<T>& a, size_t size, size_t root)
	//{
	//	size_t child = root * 2 + 1;  //计算左孩子

	//	while (child < size)
	//	{
	//		if (child + 1 < size && cmp()(a[child + 1],a[child]))
	//		{
	//			++child;
	//		}
	//		if (cmp()(a[child],a[root]))  //第一次这里出错！注意参数前后顺序！
	//		{
	//			std::swap(a[root], a[child]);
	//			root = child;
	//			child = root * 2 + 1;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}

	//void AdjustUp(vector<T>& a, size_t size, size_t root)
	//{
	//	size_t parent = (root - 1) / 2;  //计算父节点

	//	while (parent >= 0 && parent < size)  //注意这里条件，否则可能会导致死循环！
	//	{
	//		if (cmp()(a[root],a[parent]))  //注意这里参数的顺序！
	//		{
	//			std::swap(a[root], a[parent]);
	//			//AdjustDown(a,size,root);
	//			root = parent;
	//			parent = (root - 1) / 2;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}


private:
	vector<T> _hp;
	size_t _size;
};



void Test1()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	size_t size = sizeof(a) / sizeof(int);
	Heap<int,Greater<int>> hp(a, size);  //大堆
	hp.CreatHeap();

	hp.Pop();
	hp.Push(23);
}

void Test2()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	size_t size = sizeof(a) / sizeof(int);
	Heap<int, Less<int>> hp(a, size);  //小堆
	hp.CreatHeap();

	hp.Pop();
	hp.Push(3);
}