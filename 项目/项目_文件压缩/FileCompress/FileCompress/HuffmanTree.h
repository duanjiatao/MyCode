#pragma once
#include<iostream>
#include<cassert>
#include "Heap.h"

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _weight;

	HuffmanTreeNode<T>(const T& x)
		: _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		,_weight(x)
	{}
};

template<class T>
struct NodeCompare
{
	bool operator()(const HuffmanTreeNode<T>* node1, const HuffmanTreeNode<T>* node2)
	{
		return (node1->_weight)< (node2->_weight);
	}
};


template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	~HuffmanTree()
	{
		_DestroyTree(_root);
		_root = NULL;
	}

	void CreateTree(const T* a, size_t size, const T& invalid)
	{
		assert(a);

		Heap<Node*, NodeCompare<T>> minHeap;
		for (size_t i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
			{
				Node* node = new Node(a[i]);
				minHeap.Push(node);
			}
		}

		while (minHeap.Size() > 1)
		{
			Node* leftChild = minHeap.Top();
			minHeap.Pop();
			Node* rightChild = minHeap.Top();
			minHeap.Pop();

			Node* parentNode = new Node(leftChild->_weight + rightChild->_weight);
			parentNode->_left = leftChild;
			parentNode->_right = rightChild;
			leftChild->_parent = parentNode;
			rightChild->_parent = parentNode;

			minHeap.Push(parentNode);
		}

		_root = minHeap.Top();
		minHeap.Pop();
	}

	HuffmanTreeNode<T>* GetRoot()
	{
		return _root;
	}

protected:
	void _DestroyTree(HuffmanTreeNode<T>*& root)  //销毁树
	{
		if (NULL == root)
			return;

		//后序遍历删除结点
		_DestroyTree(root->_left);
		_DestroyTree(root->_right);
		delete root;
		root = NULL;
	}

protected:
	HuffmanTreeNode<T>* _root;
};


//void Test1()
//{
//	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
//	size_t n = sizeof(a)/sizeof(int);
//	HuffmanTree<int> HT;
//	HT.CreateTree(a, n, 0);
//}