#pragma once
#include<iostream>
using namespace std;

template<class K,int M = 3>
struct BTreeNode
{
	K _keys[M];  //关键字数组
	BTreeNode<K, M>* _subs[M + 1];  //孩子数组
	size_t _size;  //有效关键字个数
	BTreeNode<K, M>* _parent;

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (size_t i = 0; i < M + 1; ++i)
		{
			_subs[i] = NULL;
		}
	}
};

template<class K,class V>
struct Pair
{
	K _first;
	V _second;

	Pair(const K& k = K(),const V& v = V())
		:_first(k)
		, _second(v)
	{}
};

template<class K,int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;

public:
	BTree()
		:_root(NULL)
	{}

	~BTree()
	{}

	bool Insert(const K& key)
	{
		if (NULL == _root)
		{
			_root = new Node;
			_root->_keys[0] = key;
			++_root->_size;

			return true;
		}

		Pair<Node*, int> ret = Find(key);
		if (ret._second != -1)  //说明该节点存在
		{
			return false;
		}

		Node* cur = ret._first;
		Node* sub = NULL;
		K k = key;

		_InsertKey(cur, k, sub);  //先插入
		while (1)
		{
			if (cur->_size < M)
			{
				return true;
			}

			//分裂
			int boundary = M / 2;
			int index = 0;
			int size = cur->_size;
			Node* tmp = new Node;

			//将cur中boundary后的key值复制到tmp中
			for (int i = boundary + 1; i < size; ++i)
			{
				tmp->_keys[index++] = cur->_keys[i];
				++tmp->_size;
				--cur->_size;
			}

			//将cur中boundary后的sub复制到tmp中
			index = 0;
			for (int i = boundary + 1; i < size + 1; ++i)
			{
				tmp->_subs[index] = cur->_subs[i];
				if (tmp->_subs[index])
				{
					tmp->_subs[index]->_parent = tmp;
				}

				++index;
			}

			//将boundary对应的key取出，后面插入
			k = cur->_keys[boundary];
			--cur->_size;

			Node* parent = cur->_parent;
			if (parent == NULL)  //说明到了根节点
			{
				_root = new Node;
				_root->_keys[0] = k;
				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;
				++_root->_size;

				cur->_parent = _root;
				tmp->_parent = _root;

				return true;
			}
			else
			{
				_InsertKey(parent, k, sub);
				ret = Find(k);
				cur = ret._first;
				int i = ret._second + 1;
				cur->_subs[i] = tmp;
				tmp->_parent = cur;
			}
		}
	}

	Pair<Node*, int> Find(const K& key)
	{
		//注意这里不需要再判断_root是否为空！
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			int index = 0;
			while (index < cur->_size && cur->_keys[index] < key)
			{
				++index;
			}

			if (cur->_keys[index] == key)
			{
				return Pair<Node*, int>(cur, index);
			}

			//index > cur->_size 或 cur->_keys[index] > key
			parent = cur;
			cur = cur->_subs[index];
		}

		return Pair<Node*, int>(parent, -1);
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}


protected:
	void _InsertKey(Node* cur, K& key, Node* sub)
	{
		int index = cur->_size - 1;
		while (index >= 0)
		{
			if (cur->_keys[index] > key)
			{
				cur->_keys[index + 1] = cur->_keys[index];
				cur->_subs[index + 2] = cur->_subs[index + 1];
				--index;
			}
			else
			{
				break;
			}
		}

		cur->_keys[index + 1] = key;
		cur->_subs[index + 2] = sub;
		++cur->_size;

		if (sub)
		{
			sub->_parent = cur;
		}
	}

	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		for (size_t i = 0; i < root->_size; ++i)
		{
			_Inorder(root->_subs[i]);
			cout << root->_keys[i] << " ";
		}

		_Inorder(root->_subs[root->_size]);
	}

protected:
	Node* _root;
};


void TestBTree()
{
	BTree<int> bt;
	//int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };

	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; ++i)
	{
		bt.Insert(a[i]);
	}
	bt.Insert(150);
	bt.Insert(143);

	bt.Inorder();
}
