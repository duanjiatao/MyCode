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

	void CreatHeap()  // �� ��/С ��
	{
		for (int i = (_size-2)/2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}

	void Pop()  //ɾ�� �Ѷ�
	{
		if (_size == 0)
			return;

		std::swap(_hp[0], _hp[_size - 1]);
		--_size;
		_hp.pop_back();
		AdjustDown(0);  //���µ���
	}

	void Push(const T& x)  //�嵽 ��β
	{
		_hp.push_back(x);
		++_size;
		AdjustUp(_size - 1);  //���ϵ���
	}

	T& Top()  //ȡ �Ѷ�
	{
		if (_size > 0)
			return _hp[0];
	}

	bool Empty()  //�� �п�
	{
		return _size == 0;
	}

	

protected:

	void AdjustDown(size_t root)
	{
		size_t child = root * 2 + 1;  //��������

		while (child < _size)
		{
			if (child + 1 < _size && cmp()(_hp[child + 1], _hp[child]))
			{
				++child;
			}
			if (cmp()(_hp[child], _hp[root]))  //��һ���������ע�����ǰ��˳��
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
		size_t parent = (root - 1) / 2;  //���㸸�ڵ�

		while (parent > 0)  //ע������������������ܻᵼ����ѭ����
		{
			if (cmp()(_hp[root], _hp[parent]))  //ע�����������˳��
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
	//	size_t child = root * 2 + 1;  //��������

	//	while (child < size)
	//	{
	//		if (child + 1 < size && cmp()(a[child + 1],a[child]))
	//		{
	//			++child;
	//		}
	//		if (cmp()(a[child],a[root]))  //��һ���������ע�����ǰ��˳��
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
	//	size_t parent = (root - 1) / 2;  //���㸸�ڵ�

	//	while (parent >= 0 && parent < size)  //ע������������������ܻᵼ����ѭ����
	//	{
	//		if (cmp()(a[root],a[parent]))  //ע�����������˳��
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
	Heap<int,Greater<int>> hp(a, size);  //���
	hp.CreatHeap();

	hp.Pop();
	hp.Push(23);
}

void Test2()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	size_t size = sizeof(a) / sizeof(int);
	Heap<int, Less<int>> hp(a, size);  //С��
	hp.CreatHeap();

	hp.Pop();
	hp.Push(3);
}