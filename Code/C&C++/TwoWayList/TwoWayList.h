#include<iostream>
#include<assert.h>

using namespace std;

typedef int DataType;

struct ListNode
{

	ListNode(const DataType& x)
	: _data(x)
	, _next(NULL)
	, _prev(NULL)
	{}
	DataType _data;
	ListNode* _next;
	ListNode* _prev;
};

class List
{
public:
	List()
		:_head(NULL)
		,_tail(NULL)
	{}

	~List()
	{
		Clear();
	}

	void Clear()  //清理
	{
		ListNode* cur = _head;
		ListNode* tmp = NULL;
		while (cur)
		{
			tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
	}

	List(const List& L)
		:_head(NULL)
		, _tail(NULL)
	{
		ListNode* begin = L._head;
		while (begin)
		{
			this->PushBack(begin->_data);
			begin = begin->_next;
		}
	}

	List& operator=(List L)
	{
		if (this != &L)
		{
			this->Swap(L);
		}

		return *this;
	}


	void Print()
	{
		ListNode* cur = _head;
		while (cur)
		{
			cout << cur->_data << "->";
			cur = cur->_next;
		}
		cout << "NULL" << endl;
	}

	void Swap(List& L)
	{
		swap(_head, L._head);
		swap(_tail, L._tail);
	}

	void PushBack(const DataType& x)
	{
		ListNode* NewNode = new ListNode(x);

		if (_head == NULL)  //空链表
		{
			_head = NewNode;
			_tail = NewNode;
		}
		else
		{
			_tail->_next = NewNode;
			NewNode->_prev = _tail;
			_tail = NewNode;
		}
	}

	void PushFront(const DataType& x)
	{
		ListNode* NewNode = new ListNode(x);
		if (_head == NULL)  //空链表
		{
			_head = NewNode;
			_tail = NewNode;
		}
		else
		{
			NewNode->_next = _head;
			_head->_prev = NewNode;
			_head = NewNode;
		}
	}

	void PopBack()
	{
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			ListNode* tmp = _tail->_prev;
			tmp->_next = NULL;
			delete _tail;
			_tail = tmp;
		}
	}

	void PopFront()
	{
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			ListNode* tmp = _head->_next;
			tmp->_prev = NULL;
			delete _head;
			_head = tmp;
		}
	}

	void Insert(const ListNode* pos, const DataType& x)  //在节点后面插入
	{
		assert(pos);
		if (pos == _tail)
		{
			this->PushBack(x);
			return;
		}
		else
		{
			ListNode* NewNode = new ListNode(x);
			ListNode* cur = _head;
			while (cur)
			{
				if (cur == pos)
				{
					ListNode* tmp = cur->_next;
					NewNode->_next = tmp;
					tmp->_prev = NewNode;
					cur->_next = NewNode;
					NewNode->_prev = cur;
					break;
				}
				cur = cur->_next;
			}
		}
		
	}

	void Erase(const ListNode* pos)
	{
		assert(pos);
		assert(_head);
		if (pos == _head)
		{
			this->PopFront();
			return;
		}
		else if (pos == _tail)
		{
			this->PopBack();
			return;
		}
		else
		{
			ListNode* cur = _head;
			while (cur)
			{
				if (cur == pos)
				{
					ListNode* prev_tmp = cur->_prev;
					ListNode* next_tmp = cur->_next;
					ListNode* del = cur;
					prev_tmp->_next = next_tmp;
					next_tmp->_prev = prev_tmp;
					delete del;
					del = NULL;
					break;
				}
				cur = cur->_next;
			}
		}
	}

	ListNode* Find(const DataType& x)
	{
		ListNode* cur = _head;
		while (cur)
		{
			if (cur->_data == x)
				return cur;
		
			cur = cur->_next;
		}

		return NULL;
	}


private:
	ListNode* _head;
	ListNode* _tail;

};