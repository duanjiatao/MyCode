#pragma once
#include<iostream>
#include<string>
using namespace std;

/*线性探测*/

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
struct GetKey  //内置类型
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>  
struct GetKey<string>  //string 特化版
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());  //	（算法）
	}
};

enum Status
{
	EXIST,  // 存在
	DELETE, // 已删除
	EMPTY,  // 不存在
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
			_status[i] = EMPTY;  //初始化为空
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
		// 检查容量（负载因子）
		if ((_size * 10/_capacity) >= 8)
		{
			HashTable NewHT = HashTable(_capacity * 2);  //增容

			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST)
				{
					NewHT.Insert(_tables[i]);  //递归(下一次进去一定会满足)
				}
			}

			this->Swap(NewHT);  //更新_tables //自动释放NewHT
		}

		size_t index = HashFunc(key);
		while (_status[index] == EXIST)  //不会陷入死循环
		{								 //一定会插入成功
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}

		//找到位置进行插入
		_tables[index] = key;
		_status[index] = EXIST;
		++_size;
		return true;
	}

	bool Remove(const K& key)
	{
		int index = Find(key);  //查找下标
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

		return -1;  //找不到
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

	size_t HashFunc(const K& key)  //封装
	{
		GK gt;
		return gt(key) % _capacity;
	}

	void Swap(HashTable& ht)  // 注意：这里必须是引用，已经被坑过了！
	{
		std::swap(_tables, ht._tables);
		std::swap(_size, ht._size);
		std::swap(_capacity, ht._capacity);
		std::swap(_status, ht._status);
	}


protected:
	K* _tables;			//散列表
	size_t _size;		//数据个数
	size_t _capacity;	//容量
	Status* _status;    //状态表
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
	ht1.Insert(62);  //发生增容
	ht1.Print();

	HashTable<string> ht2(5);
	ht2.Insert("张三");
	ht2.Insert("李四");
	ht2.Insert("王五");
	ht2.Insert("赵六");
	ht2.Insert("马七");
	ht2.Print();

}

void Test2()
{
	HashTable<string> ht1(5);
	ht1.Insert("张三");
	ht1.Insert("李四");
	ht1.Insert("王五");
	ht1.Insert("赵六");
	ht1.Insert("马七");
	ht1.Print();

	ht1.Remove("张三");
	ht1.Print();
	ht1.Insert("老王");
	ht1.Print();

}