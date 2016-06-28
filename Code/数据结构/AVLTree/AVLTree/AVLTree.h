#pragma once
#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;  //平衡因子
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	AVLTreeNode(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;

public:

	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	bool Insert(const K& key, const V& value)
	{
		if (NULL == _root)  //空树
		{
			_root = new Node(key, value);
			return true;
		}

		//找位置
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			parent = cur;
			if (key < cur->_key)
				cur = cur->_left;
			else if (key > cur->_key)
				cur = cur->_right;
			else
				return false;
		}

		//插节点
		cur = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
			
		//调整平衡因子
		bool IsAdiust = false;
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			if (parent->_bf > 1 || parent->_bf < -1)  //2或-2
			{
				if (parent->_bf > 1)  //2
				{
					if (parent->_right->_bf == 1)  //2 1 0
					{
						_Roate_L(parent);  //左单旋
					}
					else if (parent->_right->_bf == -1)
					{
						_Roate_RL(parent);  //右左双旋
					}
				}
				else if (parent->_bf < -1)  //-2
				{
					if (parent->_left->_bf == -1)
					{
						_Roate_R(parent);
					}
					else if (parent->_left->_bf == 1)
					{
						_Roate_LR(parent);
					}
				}
				
				IsAdiust = true;
			}

			//让父节点指下来
			if (IsAdiust)  //发生了调整(此处可以写在旋转中)
			{
				Node* pparent = parent->_parent;
				if (pparent)
				{
					if (pparent->_key > parent->_key)
						pparent->_left = parent;
					else
						pparent->_right = parent;
				}
				else  //说明parent为根节点
				{
					_root = parent;
				}

				break;  //调整一次，循环结束
			}

			cur = parent;  //向上继续调整
			parent = cur->_parent;
		}

		return true;
	}

	bool Remove(const K& key);
	
	Node* Find(const K& key)
	{
		if (NULL == _root)
			return NULL;

		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
				cur = cur->_left;
			else if (key > cur->_key)
				cur = cur->_right;
			else
				return cur;
		}

		return NULL;
	}
	
	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}

protected:
	void _Roate_L(Node*& parent)
	{
		Node* subR = parent->_right;

		parent->_right = subR->_left;
		if (subR->_left)
		{
			subR->_left->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		parent->_bf = subR->_bf = 0;
		parent = subR;
	}

	void _Roate_R(Node*& parent)
	{
		Node* subL = parent->_left;

		parent->_left = subL->_right;
		if (subL->_right)
		{
			subL->_right->_parent = parent;
		}

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		parent->_bf = subL->_bf = 0;
		parent = subL;
	}

	void _Roate_RL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//右单旋
		subR->_left = subRL->_right;
		if (subRL->_right)
		{
			subRL->_right->_parent = subR;
		}

		subRL->_right = subR;
		subRL->_parent = parent;
		subR->_parent = subRL;

		if (subRL->_bf == 0 || subRL->_bf == 1)
		{
			subR->_bf = 0;
		}
		else
		{
			subR->_bf = 1;
		}

		//左单旋
		parent->_right = subRL->_left;
		if (subRL->_left)
		{
			subRL->_left->_parent = parent;
		}

		subRL->_left = parent;
		subRL->_parent = parent->_parent;
		parent->_parent = subRL;
		
		if (subRL->_bf == 0 || subRL->_bf == -1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
		}
		subRL->_bf = 0;

		parent = subRL;
	}

	void _Roate_LR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//左单旋
		subL->_right = subLR->_left;
		if (subLR->_left)
		{
			subLR->_left->_parent = subL;
		}

		subLR->_left = subL;
		subLR->_parent = parent;
		subL->_parent = subLR;

		if (subLR->_bf == 0 || subLR->_bf == -1)
		{
			subL->_bf = 0;
		}
		else
		{
			subL->_bf = -1;
		}

		//右单旋
		parent->_left = subLR->_right;
		if (subLR->_right)
		{
			subLR->_right->_parent = parent;
		}

		subLR->_right = parent;
		subLR->_parent = parent->_parent;
		parent->_parent = subLR;

		if (subLR->_bf == 0 || subLR->_bf == 1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = 1;
		}
		subLR->_bf = 0;

		parent = subLR;
	}

	void _Inorder(Node* root)
	{
		if (root == NULL)
			return;

		_Inorder(root->_left);
		cout << root->_key << " : " << root->_bf << endl;
		_Inorder(root->_right);
	}

	int _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		size_t depthL = _Depth(root->_left) + 1;
		size_t depthR = _Depth(root->_right) + 1;

		return depthL > depthR ?  depthL : depthR;
	}

	bool _IsBalanceTree(Node* root)
	{
		if (root == NULL)
			return true;

		bool L = _IsBalanceTree(root->_left);
		bool R = _IsBalanceTree(root->_right);

		int bf = _Depth(root->_right) - _Depth(root->_left);
		if (bf >= -1 && bf <= 1)
		{
			return true;
		}
		else
		{
			cout << root->_key << " 的平衡因子有问题" << endl;
			return false;
		}

		return L && R;
	}

	void  _Destory(Node* root)
	{
		if (NULL == root)
			return;

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
		root = NULL;
	}

protected:
	Node* _root;
};


void Test1()
{
	AVLTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		t1.Insert(a[i], i);
	}

	t1.Inorder();
	cout << t1.IsBalanceTree() << endl;
}

void Test2()
{
	AVLTree<int, int> t1;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		t1.Insert(a[i], i);
	}

	t1.Inorder();
	cout << t1.IsBalanceTree() << endl;
}