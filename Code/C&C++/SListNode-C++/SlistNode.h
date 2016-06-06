#pragma once

#include<assert.h>


typedef int DataType;

struct SlistNode
{
	SlistNode(const DataType& x)
		:_data(x)
		, _next(NULL)
	{}

	DataType _data;
	SlistNode* _next;
};

class Slist
{
public:
	Slist()
		:_head(NULL)
		, _tail(NULL)
	{}

	~Slist()
	{
		Clear();
	}

	void Clear()  //清理内存
	{
		SlistNode* cur = _head;
		SlistNode* cur_next = NULL;
		while (cur)
		{
			cur_next = cur->_next;
			delete cur;
			cur = cur_next;
		}
		_head = _tail = NULL;
	}

	Slist(const Slist& s)  //拷贝构造函数（传引用）
		:_head(NULL)
		, _tail(NULL)
	{
		SlistNode* cur = s._head;
		while (cur)
		{
			this->PushBack(cur->_data);
			cur = cur->_next;
		}

		_tail = s._tail;
	}

	/*Slist& operator=(const Slist& s)
	{
		if (this != &s)
		{
			Slist tmp(s);
			this->Swap(tmp);
		}
		return *this;
	}*/

	Slist& operator=(Slist s)  //直接传值
	{
		this->Swap(s);
		return *this;
	}

	void Swap(Slist& s)
	{
		std::swap(_head, s._head);
		std::swap(_tail, s._tail);
	}

	void Print()
	{
		SlistNode* cur = _head;
		while (cur)
		{
			cout << cur->_data << "->";
			cur = cur->_next;
		}
		cout << "NULL" << endl;

	}

	void PushBack(const DataType& x)
	{
		SlistNode* NewNode = new SlistNode(x);
		if (_head == NULL)
		{
			_head = _tail = NewNode;
		}
		else
		{
			_tail->_next = NewNode;
			_tail = NewNode;
		}
	}

	void PushFront(const DataType& x)
	{
		SlistNode* NewNode = new SlistNode(x);
		if (_head == NULL)
		{
			_head = _tail = NewNode;
		}
		else
		{
			NewNode->_next = _head;
			_head = NewNode;
		}
	}
	void PopBack()
	{
		if (_head == _tail)  //只有一个节点或者是空链表
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			SlistNode* begin = _head;
			while (begin->_next != _tail)
			{
				begin = begin->_next;
			}
			begin->_next = NULL;
			delete _tail;
			_tail = begin;
		}
	}

	void PopFront()
	{
		if (_head == _tail)  //只要一个节点或者为空链表
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			SlistNode* cur = _head->_next;
			delete _head;
			_head = NULL;
			_head = cur;
		}
	}

	void Insert(SlistNode* pos, const DataType& x)  //在pos后插入x
	{
		//assert(pos);  //最后还是判断一下

		SlistNode* NewNode = new SlistNode(x);
		if (_head == NULL)   //可以给空表插入数据
		{
			_head = _tail = NewNode;
			return;
		}
		else if (pos==_tail)  //相当于尾插
		{
			this->PushBack(x);
			return;
		}
		else
		{
			SlistNode* cur = _head;
			while (cur)
			{
				if (cur == pos)
				{
					NewNode->_next = cur->_next;
					cur->_next = NewNode;

					break;  //插入后终止循环
				}
				cur = cur->_next;
			}
		}
	}

	void Erase(SlistNode* pos)  //删除
	{
		assert(pos);
		assert(_head);  //判断是否为空链表
		
		if (pos == _head)  //相当于头删
		{
			this->PopFront();
			return;
		}
		else if (pos == _tail)  //相当于尾删
		{
			this->PopBack();
			return;
		}
		else
		{
			SlistNode* cur = _head;
			while (cur)
			{
				if (cur->_next == pos)
				{
					SlistNode* prev_tmp = cur;
					SlistNode* next_tmp = cur->_next->_next;
					SlistNode* del = cur->_next;
					prev_tmp->_next = next_tmp;
					delete del;
					del = NULL;

					break;
				}
				cur = cur->_next;
			}
		}
		

	}

	SlistNode* Find(const DataType& x)
	{
		SlistNode* begin = _head;
		while (begin)
		{
			if (begin->_data == x)
			{
				return begin;
			}
			begin = begin->_next;
		}
		return NULL;
	}

	void Reverse()  //逆置单链表
	{
		/*if (_head == NULL || _head->_next == NULL)
			return;*/

		if (_head == _tail)  //空链表或者只有一个节点
			return;

		SlistNode* cur = _head;
		SlistNode* next = NULL;
		SlistNode* NewHead = NULL;

		while (cur)
		{
			next = cur->_next;
			cur->_next = NewHead;
			NewHead = cur;

			cur = next;
		}
		_tail = _head;  //必须先更新尾节点
		_head = NewHead;

	}

	void PrintTailToHead()
	{
		_PrintTailToHead(_head);
		cout << endl;
	}

	void SortList()  //对单链表进行排序
	{
		if (_head == NULL || _head->_next == NULL)
			return;

		SlistNode* prev = NULL;
		SlistNode* cur = NULL;
		SlistNode* end = NULL;  //用来记录当前待排序列的最后一个节点
		while (end != _head)
		{
			prev = _head;
			cur = _head->_next;

			while (cur != end)
			{
				if (prev->_data > cur->_data)
					std::swap(prev->_data, cur->_data);

				prev = cur;
				cur = prev->_next;
			}

			end = prev;  //更新最后节点
		}
	}

	SlistNode* FindTailK(int k)
	{
		if (NULL == _head || k <= 0)
			return NULL;

		SlistNode* slow = _head;
		SlistNode* fast = _head;

		while (--k && fast)  //有倒数第k个数一定有正数第k个数！
		{
			fast = fast->_next;
		}

		if (NULL == fast)  //k太大了
			return NULL;

		while (fast->_next)
		{
			fast = fast->_next;
			slow = slow->_next;
		}

		return slow;
	}

protected:
	void _PrintTailToHead(SlistNode* head)
	{
		if (head == NULL)
		{
			cout << "NULL->";
			return;
		}

		_PrintTailToHead(head->_next);  //递归

		cout << head->_data << "->";

	}

private:
	SlistNode* _head;
	SlistNode* _tail;
};


 