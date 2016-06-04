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

	void InOrderThread()  //中序遍历线索化
	{
		BinaryTreeNodeThd<T>* pre = NULL;
		_InOrderThread(_root, pre);
	}

	void Inorder()  //中序线索化二叉树的中序遍历
	{
		_InOrder(_root);
	}

	void PreOrderThread()  //前序遍历线索化
	{
		BinaryTreeNodeThd<T>* pre = NULL;
		_PreOrderThread(_root, pre);
	}

	void PreOrder()  //前序线索化二叉树的前序遍历
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

	void _DestroyTree(BinaryTreeNodeThd<T>*& root)  //销毁二叉树
	{
		if (NULL == root)
			return;

		//后序遍历删除结点
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

		//先序遍历创建树
		BinaryTreeNodeThd<T>* cur = new BinaryTreeNodeThd<T>(root->_data);
		cur->_left = _Copy(root->_left);
		cur->_right = _Copy(root->_right);

		_root = cur;
		return cur;
	}

	//中序遍历线索化
	void _InOrderThread(BinaryTreeNodeThd<T>* cur, BinaryTreeNodeThd<T>*& prev)
	{																// 此处必须传引用！
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
	
	//中序遍历中序线索化的二叉树
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
			cout << root->_data << " ";  //最左节点

			while (root->_right != NULL && root->rightTag == THREAD)
			{
				root = root->_right;
				cout << root->_data << " ";
			}

			root = root->_right;

		}
		cout << endl;
	}

	//先序线索化二叉树
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

		if (cur->leftTag == LINK)  //注意这里递归条件！
			_PreOrderThread(cur->_left, prev);
		if (cur->rightTag == LINK)
			_PreOrderThread(cur->_right, prev);
	}

	//先序遍历先序线索化二叉树
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
			root = root->_right;  //直接跳到右子树
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