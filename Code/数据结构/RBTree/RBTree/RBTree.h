#include<iostream>
using namespace std;

enum color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	color _col;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& key, const V& value, color col = RED)
		:_key(key)
		, _value(value)
		, _col(col)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;

public:
	RBTree()
		:_root(NULL)
	{}

	~RBTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	bool Insert(const K&key, const V& value)
	{
		if (NULL == _root)
		{
			_root = new Node(key, value, BLACK);  //根节点为黑
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

		//插入
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
			
		//调整树
		Adjust(cur);
		_root->_col = BLACK;  //将根节点置为黑
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}


protected:

	void Adjust(Node* cur)
	{
		Node* parent = cur->_parent;
		Node* uncle = NULL;
		while (parent)
		{
			//3种情况
			if (cur->_col == RED && parent->_col == RED)
			{
				Node* gparent = parent->_parent;  //祖父节点，一定存在
				if (parent == gparent->_left)
					uncle = gparent->_right;
				else
					uncle = gparent->_left;

				//第一种情况（cur为红，parent为红，uncle存在且为红）
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					gparent->_col = RED;

					cur = gparent;  //从此节点继续往上调整
					parent = cur->_parent;
				}
				else  //cur为红，parent为红，uncle不存在或为黑
				{
					if (parent == gparent->_left && cur == parent->_left)
					{
						_Rotate_R(gparent);  //右单旋
					}
					else if (parent == gparent->_right && cur == parent->_right)
					{
						_Rotate_L(gparent);  //左单旋
					}
					else if (parent == gparent->_left && cur == parent->_right)
					{
						_Rotate_L(parent);   //先对parent左单旋
						_Rotate_R(gparent);  //再对gparent右单旋
					}
					else
					{
						_Rotate_R(parent);   //先对parent右单旋
						_Rotate_L(gparent);  //再对gparent左单旋
					}

					break;  //无需继续调整
				}
			}
			else  //不需要调整
			{
				break;
			}
		}
	}

	void _Rotate_R(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//先变色
		parent->_col = RED;
		subL->_col = BLACK;

		//后旋转
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		
		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		//将当前节点(subL)的父节点连下来
		Node* gparent = subL->_parent;
		if (gparent)
		{
			if (subL->_key < gparent->_key)
				gparent->_left = subL;
			else
				gparent->_right = subL;
		}
		else
		{
			_root = subL;
		}
	}

	void _Rotate_L(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//先变色
		parent->_col = RED;
		subR->_col = BLACK;

		//后旋转
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		//将当前节点(subR)的父节点连下来
		Node* gparent = subR->_parent;
		if (gparent)
		{
			if (subR->_key < gparent->_key)
				gparent->_left = subR;
			else
				gparent->_right = subR;
		}
		else
		{
			_root = subR;
		}
	}

	void _InOrder(Node* root)
	{
		if (NULL == root)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;

		//后续遍历删除结点
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
	RBTree<int, int> rt1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int n = sizeof(a) / sizeof(int);
	for (int i = 0; i < n; ++i)
	{
		rt1.Insert(a[i], i);
	}

	rt1.InOrder();
}