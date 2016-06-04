#pragma once
#include<iostream>
#include<cassert>
using namespace std;


typedef enum
{
	LINK,
	THREAD
}NodeTag;

template<class T>
struct BinaryTreeNodeThd
{
	BinaryTreeNodeThd(const T& x)
	:_data(x)
	, _left(NULL)
	, _right(NULL)
	, leftTag(LINK)
	, rightTag(LINK)
	{}

	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	NodeTag leftTag;
	NodeTag rightTag;
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd()
		:_root(NULL)
	{}

	BinaryTreeThd(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index);
	}

	~BinaryTreeThd()
	{
		_DestroyTree(_root);
		_root = NULL;
	}

	BinaryTreeThd(const BinaryTreeThd<T>& t)
	{
		_Copy(t._root);
	}

	BinaryTreeThd<T>& operator=(BinaryTreeThd<T> t)
	{
		std::swap(_root, t._root);
		return *this;
	}

	void InOrderThread()  //�������������
	{
		BinaryTreeNodeThd<T>* pre = NULL;
		_InOrderThread(_root, pre);
	}

	void Inorder()  //�������������������������
	{
		_InOrder(_root);
	}

	void PreOrderThread()  //ǰ�����������
	{
		BinaryTreeNodeThd<T>* pre = NULL;
		_PreOrderThread(_root, pre);
	}

	void PreOrder()  //ǰ����������������ǰ�����
	{
		_PreOrder(_root);
	}
	

protected:
	BinaryTreeNodeThd<T>* _CreateTree(const T*& a, size_t size, size_t& index)
	{
		assert(a);
		BinaryTreeNodeThd<T>* NewNode = NULL;
		if (index < size && '#' != a[index])
		{
			NewNode = new BinaryTreeNodeThd<T>(a[index]);
			NewNode->_left = _CreateTree(a, size, ++index);
			NewNode->_right = _CreateTree(a, size, ++index);
		}
		return NewNode;
	}

	void _DestroyTree(BinaryTreeNodeThd<T>*& root)  //���ٶ�����
	{
		if (NULL == root)
			return;

		//�������ɾ�����
		if (root->leftTag == LINK)
			_DestroyTree(root->_left);
		if (root->rightTag == LINK)
			_DestroyTree(root->_right);

		delete root;
		root = NULL;
	}

	BinaryTreeNodeThd<T>* _Copy(BinaryTreeNodeThd<T>* root)
	{
		if (NULL == root)
			return NULL;

		//�������������
		BinaryTreeNodeThd<T>* cur = new BinaryTreeNodeThd<T>(root->_data);
		cur->_left = _Copy(root->_left);
		cur->_right = _Copy(root->_right);

		_root = cur;
		return cur;
	}

	//�������������
	void _InOrderThread(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
	{																// �˴����봫���ã�
		if (NULL == cur)
			return;

		_InOrderThread(cur->_left, prev);

		if (NULL == cur->_left)
		{
			cur->leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		_InOrderThread(cur->_right, prev);
	}
	
	//������������������Ķ�����
	void _InOrder(BinaryTreeNodeThd<T>* root)
	{
		if (root == NULL)
			return;

		while (root)
		{
			while (root->_left != NULL && root->leftTag == LINK)
			{
				root = root->_left;
			}
			cout << root->_data << " ";  //����ڵ�

			while (root->_right != NULL && root->rightTag == THREAD)
			{
				root = root->_right;
				cout << root->_data << " ";
			}

			root = root->_right;

		}
		cout << endl;
	}

	//����������������
	void _PreOrderThread(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
	{
		if (NULL == cur)
			return;

		if (NULL == cur->_left)
		{
			cur->leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		if (cur->leftTag == LINK)  //ע������ݹ�������
			_PreOrderThread(cur->_left, prev);
		if (cur->rightTag == LINK)
			_PreOrderThread(cur->_right, prev);
	}

	//�����������������������
	void _PreOrder(BinaryTreeNodeThd<T>* root)
	{
		if (NULL == root)
			return;

		while (root)
		{
			while (root->_left != NULL && root->leftTag == LINK)
			{
				cout << root->_data << " ";
				root = root->_left;
			}

			cout << root->_data << " ";
			root = root->_right;  //ֱ������������
		}
		cout << endl;

		/*while (root)
		{
			while (root->_left != NULL && root->leftTag == LINK)
			{
				cout << root->_data << " ";
				root = root->_left;
			}

			if (root->_right != NULL && root->rightTag == LINK)
			{
				cout << root->_data << " ";
				root = root->_right;
			}
			else if (root->_right != NULL && root->rightTag == THREAD)
			{
				cout << root->_data << " ";
				root = root->_right;
			}
			else
			{
				cout << root->_data << " ";
				break;
			}
		}
		cout << endl;*/
	}


protected:
	BinaryTreeNodeThd<T>* _root;
};


void Test1()
{
	//int array[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTreeThd<int> t1(array, sizeof(array) / sizeof(int));

	t1.InOrderThread();
	t1.Inorder();
}

void Test2()
{
	//int array[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };

	BinaryTreeThd<int> t1(array, sizeof(array) / sizeof(int));

	t1.PreOrderThread();
	t1.PreOrder();
}



void main()
{
	//Test1();
	Test2();


	system("pause");
}