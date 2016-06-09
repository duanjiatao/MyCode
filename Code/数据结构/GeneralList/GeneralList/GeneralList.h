#pragma once
#include<iostream>
#include<cassert>
using namespace std;

enum Type
{
	HEAD,   //头节点
	VALUE,  //值节点
	SUB,    //字表节点
};

struct GeneralListNode
{
	GeneralListNode(Type type, const char value = 0)
		:_type(type)
		, _next(NULL)
	{
		if (_type == VALUE)
		{
			_value = value;
		}
		else if (_type == SUB)
		{
			_subLink = NULL;
		}
		else  // 头结点，什么也不做
		{}
	}

	Type _type;  //节点类型
	GeneralListNode* _next;  //指向下一个节点
	union
	{
		char _value;  //值节点的值
		GeneralListNode* _subLink;  //指向字表的指针
	};
};

class GeneralList
{
public:
	GeneralList()
		:_head(NULL)
	{}

	GeneralList(const char* s)
	{
		assert(s);
		_head = _CreateGeneralList(s);
	}

	~GeneralList()
	{
		_DestoryGeneralList(_head);
		_head = NULL;
	}

	GeneralList(const GeneralList& g)
	{
		_head = _Copy(g._head);
	}

	GeneralList& operator=(GeneralList g)
	{
		std::swap(_head, g._head);
		return *this;
	}

	void Display()
	{
		_Display(_head);
		cout << endl;
	}

	size_t Depth()
	{
		return _Depth(_head);
	}

	size_t Size()
	{
		return _Size(_head);
	}

protected:
	GeneralListNode* _CreateGeneralList(const char*& s)
	{
		assert('(' == *s);

		GeneralListNode* NewHead = new GeneralListNode(HEAD);
		GeneralListNode* cur = NewHead;
		++s;

		while (*s)
		{
			if (*s == '(')  //遇到字表
			{
				GeneralListNode* subNode = new GeneralListNode(SUB);
				cur->_next = subNode;
				cur = cur->_next;

				cur->_subLink = _CreateGeneralList(s);
			}
			else if (*s == ')')
			{
				++s;
				break;
			}
			else if (IsValue(*s))
			{
				GeneralListNode* valueNode = new GeneralListNode(VALUE,*s);
				cur->_next = valueNode;
				cur = cur->_next;
				++s;
			}
			else  // 逗号之类
			{
				++s;
			}
		}

		return NewHead;
	}
		
	bool IsValue(const char& c)
	{
		if (c >= 'a' && c <= 'z' ||
			c >= 'A' && c <= 'Z' ||
			c >= '0' && c <= '9')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void _DestoryGeneralList(GeneralListNode* head)
	{
		assert(head);

		GeneralListNode* cur = head;

		while (cur)
		{
			GeneralListNode* del = cur;
			cur = cur->_next;  //注意：此句一定要放在这里，否则会崩溃！
			if (del->_type == SUB)
			{
				_DestoryGeneralList(del->_subLink);
			}
			delete del;
			del = NULL;
		}
	}

	GeneralListNode* _Copy(GeneralListNode* head)
	{
		if (NULL == head)
			return NULL;

		GeneralListNode* cur = head;
		GeneralListNode* NewHead = new GeneralListNode(HEAD);
		GeneralListNode* NewCur = NewHead;
		cur = cur->_next;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				GeneralListNode* subNode = new GeneralListNode(SUB);
				subNode->_subLink = _Copy(cur->_subLink);
				NewCur->_next = subNode;
				NewCur = NewCur->_next;
			}
			else if (cur->_type == VALUE)
			{
				NewCur->_next = new GeneralListNode(VALUE,cur->_value);
				NewCur = NewCur->_next;
			}
			cur = cur->_next;
		}

		return NewHead;
	}

	void _Display(GeneralListNode* head)
	{
		if (NULL == head)
		{
			return;
		}

		while (head)
		{
			if (head->_type == HEAD)
			{
				cout << "(" << " ";
			}
			else if (head->_type == VALUE)
			{
				cout << head->_value << " ";
				if (head->_next)
				{
					cout << "," << " ";
				}
			}
			else
			{
				_Display(head->_subLink);
				if (head->_next)
				{
					cout << "," << " ";
				}
			}

			head = head->_next;
		}
		cout << ")" << " ";
	}

	size_t _Depth(GeneralListNode* head)
	{
		size_t depth = 1;

		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				size_t sub_depth = _Depth(cur->_subLink) + 1;
				if (sub_depth > depth)
				{
					depth = sub_depth;
				}
			}
			cur = cur->_next;
		}

		return depth;
	}

	size_t _Size(GeneralListNode* head)
	{
		size_t size = 0;

		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				size += _Size(cur->_subLink);
			}
			if (cur->_type == VALUE)
			{
				++size;
			}
			cur = cur->_next;
		}

		return size;
	}


private:
	GeneralListNode* _head;
};


void Test1()
{
	GeneralList g1("()");
	g1.Display();
	cout << "Depth : " << g1.Depth() << endl;
	cout << "Size : " << g1.Size() << endl;

	GeneralList g2("(a,b)");
	g2.Display();
	cout << "Depth : " << g2.Depth() << endl;
	cout << "Size : " << g2.Size() << endl;

	GeneralList g3("(a,b,(c,d))");
	g3.Display();
	cout << "Depth : " << g3.Depth() << endl;
	cout << "Size : " << g3.Size() << endl;

	GeneralList g4("(a,b,(c,d),(e,(f),h))");
	g4.Display();
	cout << "Depth : " << g4.Depth() << endl;
	cout << "Size : " << g4.Size() << endl;

	GeneralList g5(g4);
	g5.Display();

	GeneralList g6("()");
	g6 = g5;
	cout << endl;
	g6.Display();

}