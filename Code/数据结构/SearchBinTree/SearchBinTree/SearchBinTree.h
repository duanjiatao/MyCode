#pragma once
#include<iostream>
using namespace std;


template<class K,class V>
struct BSTNode
{
	K _key;
	V _value;

	BSTNode<K, V>* _left;
	BSTNode<K, V>* _right;

	BSTNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}

};

template<class K,class V>
class BSTree
{
	typedef BSTNode<K, V> Node;

public:
	BSTree()
		:_root(NULL)
	{}

	~BSTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

	bool Insert(const K& key, const V& value)
	{
		if (NULL == _root)  //空树
		{
			_root = new Node(key, value);
			return true;
		}

		Node* cur = _root;
		Node* prev = NULL;
		while (cur)
		{
			prev = cur;  //记录前一个节点

			if (key < cur->_key)
				cur = cur->_left;
			else if (key > cur->_key)
				cur = cur->_right;
			else
				return false;  //key值必须唯一
		}
		
		if (key < prev->_key)
			prev->_left = new Node(key, value);
		else
			prev->_right = new Node(key, value);

		return true;
	}

	bool Insert_R(const K& key, const V& value)  //递归版
	{
		return _Insert_R(_root, key, value);
	}

	Node* Find(const K& key)
	{
		if (NULL == _root)  //其实不必要
			return NULL;

		Node* find = _root;
		while (find)
		{
			if (key < find->_key)
				find = find->_left;
			else if (key > find->_key)
				find = find->_right;
			else
				return find;
		}

		return NULL;  //未找到
	}

	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}

	bool Remove(const K& key)
	{
		if (NULL == _root)  //其实不必要
			return false;

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)  //找待删除的节点
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else  //找到了要删除的节点
			{
				if (NULL == cur->_left) //左为空 或 右为空（两者都为空）
				{
					if (_root == cur)  //可能为根节点
					{
						_root = cur->_right;
					}
					else  //非根节点
					{
						if (parent->_key > cur->_key)  //待删除的节点为父节点的左孩子
						{
							parent->_left = cur->_right;
						}
						else  //为右孩子
						{
							parent->_right = cur->_right;
						}
					}

					delete cur;
					cur = NULL;
				}
				else if (NULL == cur->_right) //左不为空，右为空
				{
					if (_root == cur)  //可能为根节点
					{
						_root = cur->_left;
					}
					else  //非根节点
					{
						if (parent->_key > cur->_key)  //待删除的节点为父节点的左孩子
						{
							parent->_left = cur->_left;
						}
						else  //为右孩子
						{
							parent->_right = cur->_left;
						}
					}

					delete cur;
					cur = NULL;
				}
				else  //左右都不为空
				{
					//找右子树中序遍历的第一个节点（相当于后继）
					Node* RightInFirst = cur->_right;

					if (NULL == RightInFirst->_left)  //直接为要找的节点
					{
						std::swap(RightInFirst->_key, cur->_key);  //交换key和value
						std::swap(RightInFirst->_value, cur->_value);
						cur->_right = RightInFirst->_right;
					}
					else
					{
						Node* prev = NULL;  //记录要找节点的父节点
						while (RightInFirst->_left)
						{
							prev = RightInFirst;
							RightInFirst = RightInFirst->_left;  //一直往左走
						}
						std::swap(RightInFirst->_key, cur->_key);  //交换key和value
						std::swap(RightInFirst->_value, cur->_value);
						prev->_left = RightInFirst->_right;
					}

					delete RightInFirst;
					RightInFirst = NULL;
				}

				return true;
			}
		}

		return false;  //没找到要删除的节点
	}

	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	void Inorder()  //中序遍历
	{ 
		_Inorder(_root);
		cout << endl;
	}

protected:

	bool _Insert_R(Node*& root, const K& key, const V& value)
	{
		if (NULL == root)
		{
			root = new Node(key, value);
			return true;
		}

		if (key < root->_key)
			return _Insert_R(root->_left, key, value);
		else if (key > root->_key)
			return _Insert_R(root->_right, key, value);
		else
			return false;
		
	}

	Node* _Find_R(Node* root, const K& key)
	{
		if (NULL == root)
			return NULL;

		if (key < root->_key)
			return _Find_R(root->_left, key);
		else if (key > root->_key)
			return _Find_R(root->_right, key);
		else
			return root;
	}

	bool _Remove_R(Node*& root, const K& key)  //传引用
	{
		if (NULL == root)
			return false;

		if (key < root->_key)
			return _Remove_R(root->_left, key);
		else if (key > root->_key)
			return _Remove_R(root->_right, key);
		else
		{
			if (root->_left == NULL)  //左为空
			{
				Node* tmp = root->_right;
				delete root;
				root = tmp;
			}
			else if (root->_right == NULL)  //右为空
			{
				Node* tmp = root->_left;
				delete root;
				root = tmp;
			}
			else  //都不为空
			{
				Node* RightInFirst = root->_right;  //右子树中序遍历的第一个节点
				if (RightInFirst->_left == NULL)  //特殊情况
				{
					std::swap(RightInFirst->_key, root->_key); //交换key和value
					std::swap(RightInFirst->_value, root->_value);
					root->_right = RightInFirst->_right;
					
					delete RightInFirst;
					RightInFirst = NULL;
				}
				else
				{
					Node* prev = NULL;
					while (RightInFirst->_left)
					{
						prev = RightInFirst;
						RightInFirst = RightInFirst->_left;
					}
					std::swap(root->_key, RightInFirst->_key);
					std::swap(root->_value, RightInFirst->_value);
					prev->_left = RightInFirst->_right;
					
					delete RightInFirst;
					RightInFirst = NULL;
					
				}
			}

			return true;
		}
	}
	
	void _Inorder(Node* root)
	{
		if (NULL == root)
			return;

		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}

	void _Destroy(Node* root)
	{
		if (NULL == root)
			return;

		_Destroy(root->_left);
		_Destroy(root->_right);

		delete root;
		root = NULL;
	}


protected:
	Node* _root;
};

void Test1()
{
	BSTree<int, int> bst;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		bst.Insert(a[i], i);
	}

	bst.Inorder();
}

void Test2()
{
	BSTree<int, int> bst;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		bst.Insert_R(a[i], i);
	}
		bst.Inorder();

	BSTNode<int, int>* find1 = bst.Find(8);
	if (find1)
	{
		cout << "key: " << find1->_key << " ";
		cout << "value: " << find1->_value << endl;
	}

	BSTNode<int, int>* find2 = bst.Find_R(18);
	if (find2)
	{
		cout << "key: " << find2->_key << " ";
		cout << "value: " << find2->_value << endl;
	}
	
}

void Test3()
{
	BSTree<int, int> bst;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9};
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		bst.Insert_R(a[i], i);
	}
	bst.Inorder();

	for (int i = 0; i < n; ++i)
	{
		bst.Remove(a[i]);
	}

	/*for (int i = 0; i < n; ++i)
	{
		bst.Remove_R(a[i]);
	}*/

	bst.Inorder();
}