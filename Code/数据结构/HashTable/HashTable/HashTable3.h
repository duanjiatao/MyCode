#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*��ϣͰ*/

static size_t BKDRHash(const char* str)
{
	size_t seed = 131;
	size_t hash = 0;

	while (*str)  //*strת����һ������
	{
		hash = hash*seed + *str;
		++str;
	}

	return (hash & 0x7FFFFFFF);
}

template<class K>
struct GetKey  //��������
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct GetKey<string>  //string �ػ���
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K, V>* _next;

	HashTableNode()
	{}

	HashTableNode(const K& key,const V& value)
		:_next(NULL)
		, _key(key)
		, _value(value)
	{}
};

template<class K, class V, class GK = GetKey<K>>
class HashTableBucket
{
	typedef HashTableNode<K, V> KVNode;

public:
	HashTableBucket()
		:_size(0)
	{}

	HashTableBucket(size_t size)
		:_size(0)
	{
		_tables.resize(size);  // ע��˴�����size ������_size
							   // ������Զ���ʼ��Ϊ NULL
	}

	~HashTableBucket()
	{
		if (_size > 0)
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				KVNode* cur = _tables[i];
				while (cur)
				{
					KVNode* del = cur;
					cur = cur->_next;
					delete del;
					del = NULL;
				}
				_tables[i] = NULL;
			}
		}
	}

	HashTableBucket(HashTableBucket<K,V>& ht)
		:_tables(NULL)
		, _size(0)
	{
		//ֱ�ӹ���һ����ı�,������ܻ������ݣ�����Ч���½�
		HashTableBucket<K, V> newHT(ht._tables.size());  
		for (size_t i = 0; i < ht._tables.size(); ++i)
		{
			KVNode* cur = ht._tables[i];
			KVNode*& head = newHT._tables[i];

			//KVNode* head = NULL;
			while (cur)
			{
				//tmp.Insert(cur->_key, cur->_value);
				// ֱ��ͷ��
				KVNode* tmp = new KVNode(cur->_key, cur->_value);
				tmp->_next = head;
				head = tmp;

				cur = cur->_next;
			}
			//newHT._tables[i] = head;
		}

		this->Swap(newHT);
	}

	HashTableBucket<K, V>& operator=(HashTableBucket<K, V> ht)
	{
		this->Swap(ht);
		return *this;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_size == _tables.size())  //��鸺������
		{
			size_t newSize = _CheckCapacity();

			vector<KVNode*> newTables;  //ֻ��Ҫ��һ�������鼴��
			newTables.resize(newSize);  //ֱ������,�Զ���ʼ��ΪNULL

			for (size_t i = 0; i < _tables.size(); ++i)
			{
				KVNode* cur = _tables[i];
				KVNode* prev = NULL;
				while (cur)
				{
					prev = cur;
					cur = cur->_next;
					size_t index = HashFunc(prev->_key);  //ֱ��ȡ�ڵ㣬�����±�����
					prev->_next = newTables[index];
					newTables[index] = prev;
				}
			}

			std::swap(_tables, newTables);  //����newTablesʱ���������ͷŽڵ㣡����
		}

		size_t index = HashFunc(key);
		KVNode* newNode = new KVNode(key, value);

		KVNode* cur = _tables[index];
		while (cur)  //���key�Ƿ����
		{
			if (cur->_key == key)
				return false;
			cur = cur->_next;
		}
		
		newNode->_next = _tables[index];
		_tables[index] = newNode;
		++_size;
		return true;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFunc(key);
		KVNode* cur = _tables[index];
		KVNode* prev = NULL;
		while (cur && cur->_key != key)
		{
			prev = cur;
			cur = cur->_next;
		}

		if (cur == NULL)
		{
			return false;
		}
		else
		{
			if (cur == _tables[index])  //��һ���ڵ�
			{
				_tables[index] = cur->_next;
			}
			else
			{
				if (cur->_next)  //���һ���ڵ�
				{
					prev->_next = cur->_next;
				}
				else
				{
					prev->_next = NULL;
				}
			}
			
			delete cur;
			cur = NULL;
			--_size;
			return true;
		}
	}

	KVNode* Find(const K& key)
	{
		size_t index = HashFunc(key);
		KVNode* cur = _tables[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}

		return false;
	}


	void Print()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			cout << i << " : ";
			KVNode* cur = _tables[i];
			while (cur)
			{
				cout << cur->_key << ",";
				cout << cur->_value << " -> ";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}

protected:
	size_t HashFunc(const K& key)
	{
		GK gt;
		return gt(key) % _tables.size();
	}

	size_t _CheckCapacity()
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > _size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize];  //�ﵽ���ֵ
	}

	void Swap(HashTableBucket<K, V>& ht)
	{
		std::swap(_tables, ht._tables);
		std::swap(_size, ht._size);
	}
	

private:
	vector<KVNode*> _tables;
	size_t _size;
};


void Test1()
{
	HashTableBucket<int, int> ht1(10);
	ht1.Insert(0, 0);
	ht1.Insert(1, 1);
	ht1.Insert(2, 2);
	ht1.Insert(3, 3);
	ht1.Insert(4, 4);
	ht1.Insert(5, 5);
	ht1.Insert(6, 6);
	ht1.Insert(7, 7);
	ht1.Insert(8, 8);
	ht1.Insert(9, 9);  //��������
	ht1.Insert(10, 10);
	ht1.Insert(3, 3);  //����ʧ��

	ht1.Print();

	ht1.Remove(4);
	ht1.Remove(13);  //��ʧ��

	ht1.Print();
}

void Test2()
{
	HashTableBucket<string, string> ht1(10);
	ht1.Insert("�ֵ�", "dictionary");
	ht1.Insert("����", "insert");
	ht1.Insert("ɾ��", "delete");
	ht1.Insert("��ѯ", "find");
	ht1.Print();

	//cout << ht1.Find("��ѯ")->_value << endl;

	HashTableBucket<string, string> ht2(ht1);
	ht2.Print();

	/*HashTableBucket<string, string> ht3(3);
	ht3.Insert("�Ǻ�", "hehe");
	ht3.Print();
	ht3 = ht2;
	ht3.Print();*/
}
