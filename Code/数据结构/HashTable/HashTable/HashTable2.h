#pragma once
#include<iostream>
using namespace std;

/*����̽��*/

static size_t BKDRHash(const char* str)
{
	size_t seed = 131;
	size_t hash = 0;

	while (*str)
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

enum Status
{
	EXIST,  // ����
	DELETE, // ��ɾ��
	EMPTY,  // ������
};

template<class K,class V>
struct KeyValueNode
{
	K _key;
	V _value;

	KeyValueNode()
	{}

	KeyValueNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
	{}
};

template<class K, class V, class GK = GetKey<K>>
class HashTable
{
	typedef KeyValueNode<K, V> KVNode;

public:
	HashTable()
		:_tables(NULL)
		, _size(0)
		, _capacity(0)
		, _status(NULL)
	{}

	HashTable(const size_t capacity)
		:_tables(new KVNode[capacity])
		, _size(0)
		, _capacity(capacity)
		, _status(new Status[capacity])
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			_status[i] = EMPTY;
		}
	}

	HashTable(const HashTable<K, V>& ht)
		:_tables(NULL)
		, _status(NULL)
		, _size(0)
		, _capacity(0)
	{
		HashTable<K, V> newHT(ht._capacity);
		for (size_t i = 0; i < ht._capacity; ++i)
		{
			if (ht._status[i] == EXIST)  //ֻ������Ч����
			{
				newHT.Insert(ht._tables[i]._key, ht._tables[i]._value);
			}
		}

		this->Swap(newHT);
	}

	HashTable<K, V>& operator=(HashTable<K, V> ht)
	{
		this->Swap(ht);
		return *this;
	}

	~HashTable()
	{
		if (_tables)
		{
			delete[] _tables;
			delete[] _status;
			_tables = NULL;
			_status = NULL;
		}
	}

	bool Insert(const K& key, const V& value)
	{
		if (_size * 10 / _capacity == 8)  // ��鸺������
		{
			HashTable<K, V> NewHT(_capacity * 2);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST)
				{
					NewHT.Insert(_tables[i]._key, _tables[i]._value);
				}
			}

			this->Swap(NewHT);
		}

		
		size_t index = HashFunc0(key);
		size_t i = 1;
		while (_status[index] == EXIST)
		{
			if (_tables[index]._key == key)  //���key�Ƿ��Ѵ���
				return false;
			index = HashFunc2(index, i++);
		}

		KVNode newNode(key, value);
		_tables[index] = newNode;
		_status[index] = EXIST;
		++_size;
		return true;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFunc0(key);
		size_t i = 1;
		while (_status[index] != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if (_status[index] == EXIST)
				{
					_status[index] = DELETE;
					--_size;
					return true;
				}
				else
				{
					return false;
				}
			}
			index = HashFunc2(index, i++);
		}

		return false;
	}

	bool Find(const K& key)
	{
		size_t index = HashFunc0(key);
		size_t i = 1;
		while (_status[index] != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if (_status[index] == EXIST)
					return true;
				else
					return false;
			}
			index = HashFunc2(index, i++);
		}

		return false;
	}

	void Print()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << i << " status: " << _status[i];
			cout << " key: " << _tables[i]._key;
			cout<< " value: " << _tables[i]._value << endl;
		}
		cout << endl;
	}

	void PrintString()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << i << " status: " << _status[i];
			cout << " key: " << (_tables[i]._key).c_str();
			cout << " value: " << (_tables[i]._value).c_str() << endl;
		}
		cout << endl;
	}

protected:
	size_t HashFunc0(const K& key)
	{
		GK gt;
		return gt(key) % _capacity;
	}

	size_t HashFunc2(size_t index, size_t i)
	{
		index = index + 2 * i - 1;
		while (index >= _capacity)  //�˴�����ѭ��
		{
			index = index - _capacity;
		}

		return index;
	}


	void Swap(HashTable& ht)  // ע�⣺������������ã��Ѿ����ӹ��ˣ�
	{
		std::swap(_tables, ht._tables);
		std::swap(_size, ht._size);
		std::swap(_capacity, ht._capacity);
		std::swap(_status, ht._status);
	}

private:
	KVNode* _tables;
	size_t _size;
	size_t _capacity;
	Status* _status;

};


void Test1()
{
	HashTable<int, int> ht1(10);
	ht1.Insert(89, 89);
	ht1.Insert(18, 18);
	ht1.Insert(49, 49);
	ht1.Insert(58, 58);
	ht1.Insert(9, 9);
	ht1.Insert(58, 58);  //����ʧ��
	ht1.Insert(42, 42);
	ht1.Insert(94, 94);
	ht1.Insert(62, 62);  //��������
	ht1.Insert(3, 3);
	ht1.Print();

	HashTable<int, int> ht2(10);
	ht2.Insert(89, 89);
	ht2 = ht1;
	ht2.Print();
}

void Test2()
{
	HashTable<string, string> ht1(10);
	ht1.Insert("�ֵ�", "dictionary");
	ht1.Insert("����", "insert");
	ht1.Insert("ɾ��", "delete");
	ht1.Insert("����", "find,search");
	ht1.Insert("ƻ��", "apple");
	ht1.Insert("ѧϰ", "study");
	ht1.Insert("��ˣ", "paly");
	ht1.Insert("˯��", "sleep");
	ht1.Insert("����", "bullshit");  //��������

	ht1.Remove("ɾ��");
	ht1.PrintString();

	cout << ht1.Find("����") << endl;
	cout << ht1.Find("������") << endl;
}

void Test3()
{
	HashTable<string, string> ht1(10);
	ht1.Insert("�ֵ�", "dictionary");
	ht1.Insert("����", "insert");
	ht1.Insert("ɾ��", "delete");
	ht1.Insert("����", "find,search");
	ht1.Insert("˯��", "sleep");
	ht1.Insert("����", "bullshit");

	HashTable<string, string> ht2(ht1);
	//ht1.PrintString();
	ht2.PrintString();
}