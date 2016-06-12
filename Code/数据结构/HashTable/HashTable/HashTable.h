#pragma once
#include<iostream>
#include<string>
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
		return BKDRHash(key.c_str());  //	���㷨��
	}
};

enum Status
{
	EXIST,  // ����
	DELETE, // ��ɾ��
	EMPTY,  // ������
};

template<class K, class GK = GetKey<K>>
class HashTable
{
public:
	HashTable()
		:_tables(NULL)
		, _size(0)
		, _capacity(0)
		, _status(NULL)
	{}

	HashTable(size_t capacity)
		:_tables(new K[capacity])
		, _size(0)
		, _capacity(capacity)
		, _status(new Status[capacity])
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			_status[i] = EMPTY;  //��ʼ��Ϊ��
		}
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

	bool Insert(const K& key)
	{
		// ����������������ӣ�
		if ((_size * 10/_capacity) >= 8)
		{
			HashTable NewHT = HashTable(_capacity * 2);  //����

			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST)
				{
					NewHT.Insert(_tables[i]);  //�ݹ�(��һ�ν�ȥһ��������)
				}
			}

			this->Swap(NewHT);  //����_tables //�Զ��ͷ�NewHT
		}

		size_t index = HashFunc(key);
		while (_status[index] == EXIST)  //����������ѭ��
		{								 //һ�������ɹ�
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}

		//�ҵ�λ�ý��в���
		_tables[index] = key;
		_status[index] = EXIST;
		++_size;
		return true;
	}

	bool Remove(const K& key)
	{
		int index = Find(key);  //�����±�
		if (index != -1)
		{
			_status[index] = DELETE; 
			--_size;
			return true;
		}
		return false;
	}

	int Find(const K& key)
	{
		size_t index = HashFunc(key);
		while (_status[index] == EXIST)
		{
			if (_tables[index] == key)
			{
				return index;
			}

			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}

		return -1;  //�Ҳ���
	}

	void Print()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << i << " status: " << _status[i];
			cout << " key: " << _tables[i] << endl;
		}
		cout << endl;
	}

protected:

	size_t HashFunc(const K& key)  //��װ
	{
		GK gt;
		return gt(key) % _capacity;
	}

	void Swap(HashTable& ht)  // ע�⣺������������ã��Ѿ����ӹ��ˣ�
	{
		std::swap(_tables, ht._tables);
		std::swap(_size, ht._size);
		std::swap(_capacity, ht._capacity);
		std::swap(_status, ht._status);
	}


protected:
	K* _tables;			//ɢ�б�
	size_t _size;		//���ݸ���
	size_t _capacity;	//����
	Status* _status;    //״̬��
};


void Test1()
{
	HashTable<int> ht1(10);
	ht1.Insert(3);
	ht1.Insert(6);
	ht1.Insert(18);
	ht1.Insert(13);
	ht1.Insert(29);
	ht1.Insert(58);
	ht1.Insert(42);
	ht1.Insert(94);
	ht1.Insert(62);  //��������
	ht1.Print();

	HashTable<string> ht2(5);
	ht2.Insert("����");
	ht2.Insert("����");
	ht2.Insert("����");
	ht2.Insert("����");
	ht2.Insert("����");
	ht2.Print();

}

void Test2()
{
	HashTable<string> ht1(5);
	ht1.Insert("����");
	ht1.Insert("����");
	ht1.Insert("����");
	ht1.Insert("����");
	ht1.Insert("����");
	ht1.Print();

	ht1.Remove("����");
	ht1.Print();
	ht1.Insert("����");
	ht1.Print();

}