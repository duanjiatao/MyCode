#pragma once
#include<iostream>
#include<cassert>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}

	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
	:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index);
	}

	~BinaryTree()
	{
		_DestroyTree(_root);
		_root = NULL;
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_Copy(t._root);
	}

	BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		std::swap(_root, t._root);
		return *this;
	}

	void PrevOrder()  //先序遍历
	{
		//_PrevOrder(_root);  //递归
		_PrevOrder2(_root);  //非递归
		cout << endl;
	}

	void InOrder()  //中序遍历
	{
		//_InOrder(_root);  //递归
		_InOrder2(_root);  //非递归
		cout<<endl;
	}

	void PostOrder()  //后序遍历
	{
		//_PostOrder(_root);  //递归
		_PostOrder2(_root);  //非递归
		cout << endl;
	}

	void LevelOrder()  //层次遍历
	{
		_LevelOrder(_root);
	}

	int Size()  //求节点数
	{
		return _Size(_root);
	}

	int Depth()  //求深度
	{
		return _Depth(_root);
	}

	BinaryTreeNode<T>* Find(const T& x)  //查找节点
	{
		return _Find(_root, x);
	}

	int GetLeafNum()  //获取叶子节点
	{
		return _GetLeafNum(_root);
	}

protected:
	BinaryTreeNode<T>* _CreateTree(const T*& a, size_t size, size_t& index)
	{
		assert(a);
		BinaryTreeNode<T>* NewNode = NULL;
		if (index < size && '#' != a[index])
		{
			NewNode = new BinaryTreeNode<T>(a[index]);
			NewNode->_left = _CreateTree(a, size, ++index);
			NewNode->_right = _CreateTree(a, size, ++index);
		}
		return NewNode;
	}

	void _DestroyTree(BinaryTreeNode<T>*& root)  //销毁二叉树
	{
		if (NULL == root)
			return;

		//后序遍历删除结点
		_DestroyTree(root->_left);
		_DestroyTree(root->_right);
		delete root;
		root = NULL;
	}

	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (NULL == root)
			return NULL;

		BinaryTreeNode<T>* cur = new BinaryTreeNode<T>(root->_data);
		cur->_left = _Copy(root->_left);
		cur->_right = _Copy(root->_right);
		
		_root = cur;
		return cur;
	}

	void _PrevOrder(BinaryTreeNode<T>*& root)  //递归
	{
		if (NULL == root)
			return;

		BinaryTreeNode<T>* cur = root;
		cout << cur->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _PrevOrder2(BinaryTreeNode<T>*& root)  //非递归
	{
		if (NULL == root)
			return;

		stack<BinaryTreeNode<T>*> s;
		s.push(root);
		
		while (!s.empty())
		{
			BinaryTreeNode<T>* cur = s.top();
			cout << cur->_data << " ";
			s.pop();

			if (cur->_right)
				s.push(cur->_right);
			if (cur->_left)
				s.push(cur->_left);
		}
	}

	void _InOrder(BinaryTreeNode<T>*& root)  //递归
	{
		if (NULL == root)
			return;

		BinaryTreeNode<T>* cur = root;
		_InOrder(root->_left);
		cout << cur->_data << " ";
		_InOrder(root->_right);
	}

	void _InOrder2(BinaryTreeNode<T>*& root)  //非递归
	{
		if (NULL == root)
			return;

		stack<BinaryTreeNode<T>*> s;

		BinaryTreeNode<T>* cur = root;
		while (cur || !s.empty())  //多注意此处！
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			cur = s.top();  //此处不需要判断栈是否为空
			cout << cur->_data << " ";
			s.pop();
			cur = cur->_right;
		}
	}

	void _PostOrder(BinaryTreeNode<T>*& root)  //递归
	{
		if (NULL == root)
			return;

		BinaryTreeNode<T>* cur = root;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << cur->_data << " ";
	}


	void _PostOrder2(BinaryTreeNode<T>*& root)  //非递归
	{
		if (NULL == root)
			return;

		stack<BinaryTreeNode<T>*> s;
		s.push(root);
		BinaryTreeNode<T>* prev = NULL;

		while (!s.empty())
		{
			BinaryTreeNode<T>* cur = s.top();
			if (NULL == cur->_left && NULL == cur->_right ||
				prev && (cur->_left == prev || cur->_right == prev))  //此处prev判空不可少
			{
				cout << cur->_data << " ";
				s.pop();
				prev = cur;
			}
			else
			{
				if (cur->_right)  //先压右
					s.push(cur->_right);
				if (cur->_left)   //后压左
					s.push(cur->_left);
			}
		}

	}

	void _LevelOrder(BinaryTreeNode<T>*& root)
	{
		if (NULL == root)
			return;

		queue<BinaryTreeNode<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			BinaryTreeNode<T>* cur = q.front();
			cout << cur->_data << " ";
			q.pop();

			if (cur->_left)
				q.push(cur->_left);
			if (cur->_right)
				q.push(cur->_right);
		}
		cout << endl;
	}

	int _Size(BinaryTreeNode<T>*& root)
	{
		if (NULL == root)
			return 0;
		
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	int _Depth(BinaryTreeNode<T>*& root)
	{
		if (NULL == root)
			return 0;

		int leftCount = _Depth(root->_left) + 1;
		int rightCount = _Depth(root->_right) + 1;
		
		return leftCount > rightCount ? leftCount : rightCount;
	}

	int _GetLeafNum(BinaryTreeNode<T>*& root)
	{
		if (NULL == root)
			return 0;

		if (NULL == root->_left && NULL == root->_right)
			return 1;

		return _GetLeafNum(root->_left) + _GetLeafNum(root->_right);
	}

	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>*& root, const T& x)
	{
		if (NULL == root)
			return NULL;

		if (root->_data == x)
			return root;

		BinaryTreeNode<T>* tmp = _Find(root->_left, x);
		if (tmp != NULL)
			return tmp;
		else
			return _Find(root->_right, x);
	}

	int GetMaxDistance()  //获取最远的两个节点之间的距离（肯定是叶子节点）
	{
		if (NULL == _root)
			return 0;


	}


protected:
	BinaryTreeNode<T>* _root;
};



void Test1()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t1(array, 10);

	BinaryTree<int> t2(t1);

	BinaryTree<int> t3;
	t3 = t2;

}

void Test2()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t1(array, 10);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();

	cout << "Size:" << t1.Size() << endl;
	cout << "Depth:" << t1.Depth() << endl;
	cout << t1.Find(5)->_data << endl;
}

void Test3()
{
	int array[] = { 1, 2, 3, '#', '#', 4, 5, '#', '#', 6, '#', '#', 7, 8, '#', '#', 9, 10 };
	BinaryTree<int> t1(array, sizeof(array)/sizeof(int));
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	cout << "LeafNode:" << t1.GetLeafNum() << endl;
}