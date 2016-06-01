#pragma once

#include<iostream>
using namespace std;


template<class T>
struct Node
{
	Node(const T& x)
		:_data(x)
		,_next(NULL)
	{}

	T _data;
	Node<T>* _next;
};

template<class T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
	{}

	~Queue()
	{
		while (_head)
		{
			Node<T>* cur = _head;
			_head = _head->_next;
			delete cur;
		}
		_head = _tail = NULL;
	}

	Queue(const Queue<T>& q)
		:_head(NULL)
		, _tail(NULL)
	{
		Node<T>* begin = q._head;
		while (begin)
		{
			this->Push(begin->_data);
			begin = begin->_next;
		}
		//_tail = q._tail;  //不要此句也行
	}



	Queue<T>& operator=(Queue<T> q)
	{
		this->_swap(q);
		return *this;
	}

protected:
	void _swap(Queue<T>& q)
	{
		std::swap(_head, q._head);
		std::swap(_tail, q._tail);
	}

public:
	void Push(const T& x)
	{
		Node<T>* newNode = new Node<T>(x);
		if (this->Empty())
		{
			_head = _tail = newNode;
		}
		else
		{
			_tail->_next = newNode;
			_tail = newNode;
		}

	}

	void Pop()
	{
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node<T>* cur = _head->_next;
			delete _head;
			_head = NULL;
			_head = cur;
		}
	}

	Node<T>& Back()
	{
		return _tail;
	}

	Node<T>& Front()
	{
		return _head;
	}

	size_t Size()
	{
		size_t count = 0;
		Node<T>* cur = _head;
		where(cur)
		{
			++count;
			cur = cur->_next;
		}
		return count;
	}

	bool Empty()
	{
		return (_head == NULL && _tail == NULL);
	}

	void Diaplay()
	{
		Node<T>* begin = _head;
		while (begin)
		{
			cout << begin->_data << "->";
			begin = begin->_next;
		}
		cout << "NULL" << endl;
	}

protected:
	Node<T>* _head;
	Node<T>* _tail;

};