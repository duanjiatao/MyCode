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
			_root = new Node(key, value, BLACK);  //���ڵ�Ϊ��
			return true;
		}
		
		//��λ��
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

		//����
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
			
		//������
		Adjust(cur);
		_root->_col = BLACK;  //�����ڵ���Ϊ��
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
			//3�����
			if (cur->_col == RED && parent->_col == RED)
			{
				Node* gparent = parent->_parent;  //�游�ڵ㣬һ������
				if (parent == gparent->_left)
					uncle = gparent->_right;
				else
					uncle = gparent->_left;

				//��һ�������curΪ�죬parentΪ�죬uncle������Ϊ�죩
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					gparent->_col = RED;

					cur = gparent;  //�Ӵ˽ڵ�������ϵ���
					parent = cur->_parent;
				}
				else  //curΪ�죬parentΪ�죬uncle�����ڻ�Ϊ��
				{
					if (parent == gparent->_left && cur == parent->_left)
					{
						_Rotate_R(gparent);  //�ҵ���
					}
					else if (parent == gparent->_right && cur == parent->_right)
					{
						_Rotate_L(gparent);  //����
					}
					else if (parent == gparent->_left && cur == parent->_right)
					{
						_Rotate_L(parent);   //�ȶ�parent����
						_Rotate_R(gparent);  //�ٶ�gparent�ҵ���
					}
					else
					{
						_Rotate_R(parent);   //�ȶ�parent�ҵ���
						_Rotate_L(gparent);  //�ٶ�gparent����
					}

					break;  //�����������
				}
			}
			else  //����Ҫ����
			{
				break;
			}
		}
	}

	void _Rotate_R(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//�ȱ�ɫ
		parent->_col = RED;
		subL->_col = BLACK;

		//����ת
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		
		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		//����ǰ�ڵ�(subL)�ĸ��ڵ�������
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

		//�ȱ�ɫ
		parent->_col = RED;
		subR->_col = BLACK;

		//����ת
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		//����ǰ�ڵ�(subR)�ĸ��ڵ�������
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

		//��������ɾ�����
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