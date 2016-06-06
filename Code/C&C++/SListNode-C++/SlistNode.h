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

	void Clear()  //�����ڴ�
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

	Slist(const Slist& s)  //�������캯���������ã�
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

	Slist& operator=(Slist s)  //ֱ�Ӵ�ֵ
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
		if (_head == _tail)  //ֻ��һ���ڵ�����ǿ�����
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
		if (_head == _tail)  //ֻҪһ���ڵ����Ϊ������
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

	void Insert(SlistNode* pos, const DataType& x)  //��pos�����x
	{
		//assert(pos);  //������ж�һ��

		SlistNode* NewNode = new SlistNode(x);
		if (_head == NULL)   //���Ը��ձ��������
		{
			_head = _tail = NewNode;
			return;
		}
		else if (pos==_tail)  //�൱��β��
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

					break;  //�������ֹѭ��
				}
				cur = cur->_next;
			}
		}
	}

	void Erase(SlistNode* pos)  //ɾ��
	{
		assert(pos);
		assert(_head);  //�ж��Ƿ�Ϊ������
		
		if (pos == _head)  //�൱��ͷɾ
		{
			this->PopFront();
			return;
		}
		else if (pos == _tail)  //�൱��βɾ
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

	void Reverse()  //���õ�����
	{
		/*if (_head == NULL || _head->_next == NULL)
			return;*/

		if (_head == _tail)  //���������ֻ��һ���ڵ�
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
		_tail = _head;  //�����ȸ���β�ڵ�
		_head = NewHead;

	}

	void PrintTailToHead()
	{
		_PrintTailToHead(_head);
		cout << endl;
	}

	void SortList()  //�Ե������������
	{
		if (_head == NULL || _head->_next == NULL)
			return;

		SlistNode* prev = NULL;
		SlistNode* cur = NULL;
		SlistNode* end = NULL;  //������¼��ǰ�������е����һ���ڵ�
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

			end = prev;  //�������ڵ�
		}
	}

	SlistNode* FindTailK(int k)
	{
		if (NULL == _head || k <= 0)
			return NULL;

		SlistNode* slow = _head;
		SlistNode* fast = _head;

		while (--k && fast)  //�е�����k����һ����������k������
		{
			fast = fast->_next;
		}

		if (NULL == fast)  //k̫����
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

		_PrintTailToHead(head->_next);  //�ݹ�

		cout << head->_data << "->";

	}

private:
	SlistNode* _head;
	SlistNode* _tail;
};


 