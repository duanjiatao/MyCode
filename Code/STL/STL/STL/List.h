#pragma once
#include<iostream>
using namespace std;

template<class T>
struct __ListNode
{
	T _data;
	__ListNode<T>* _prev;
	__ListNode<T>* _next;

	__ListNode()
		: _prev(NULL)
		, _next(NULL)
	{}

	__ListNode(const T x)
		:_data(x)
		, _prev(NULL)
		, _next(NULL)
	{}

};

template<class T>
class __ListIterator
{
public:
	typedef __ListIterator<T> Iterator;  //迭代器
	typedef __ListNode<T>* LinkType;  //节点指针

	typedef T ValueType;  //T
	typedef T* Pointer;   //T*
	typedef T& Reference; //T&
	
	LinkType _node;

	__ListIterator(LinkType node = NULL)
		:_node(node)
	{}

	bool operator ==(const __ListIterator<T >& x) const
	{
		return this->_node == x._node;
	}
	bool operator !=(const __ListIterator<T >& x) const
	{
		return this->_node != x._node;
	}

	Reference operator*() const  //返回引用
	{
		return _node->_data;
	}

	Pointer operator->() const
	{
		return &(operator*());
	}

	Iterator& operator++()  //注意返回引用
	{
		_node = _node->_next;
		return *this;
	}

	Iterator& operator++(int)
	{
		Iterator tmp(_node);
		_node = _node->_next;

		return tmp;
	}

	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Iterator& operator--(int)
	{
		__ListIterator<T > tmp(_node);
		_node = _node->_prev;
		return tmp;
	}

};

template<class T>
class List
{
public:
	typedef T ValueType;
	typedef __ListNode<T>* LinkType;
	typedef __ListIterator<T> Iterator;

	List()
		:_head(new __ListNode<T>())
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		Clear();
	}

	/////////////////////////


	//pos之前插入
	void Insert(Iterator pos, const ValueType& x)
	{
		LinkType newNode = new __ListNode<T>(x);

		LinkType prev = pos._node->_prev;
		LinkType cur = pos._node;

		prev->_next = newNode;
		newNode->_prev = prev;

		newNode->_next = cur;
		cur->_prev = newNode;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	Iterator Erease(Iterator pos)
	{
		if (pos._node == _head)  //不能删除头结点（指针）
			return;

		if (_head->_next == _head)  //没有可删除的节点
			return;

		LinkType prev = pos._node->_prev;
		LinkType next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos._node;

		return Iterator(next);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	void Clear()
	{
		Iterator begin = Begin();
		while (begin != End())
		{
			LinkType tmp = begin._node;
			++begin;
			delete tmp;
		}
	}

private:
	LinkType _head;
};

void TestList()
{
	List<int> L;
	for (int i = 0; i < 10; ++i)
	{
		L.PushBack(i);
	}

	
	__ListIterator<int> it = L.Begin();
	while (it != L.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}