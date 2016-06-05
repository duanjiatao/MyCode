#include<iostream>
using namespace std;


//template <class T>
//class Auto_ptr
//{
//public:
//	Auto_ptr<T>(const T& x)
//		:_ptr(new T(x))
//	{}
//
//	~Auto_ptr<T>()
//	{
//		delete _ptr;
//		_ptr = NULL;
//	}
//
//	Auto_ptr<T>(Auto_ptr<T>& ap)
//		:_ptr(ap._ptr)
//	{
//		ap._ptr = NULL;
//	}
//
//	Auto_ptr<T>& operator=(Auto_ptr<T>& ap)
//	{
//		if (_ptr != ap._ptr)
//		{
//			_ptr = ap._ptr;
//			ap._ptr = NULL;
//		}
//		return *this;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//	
//	void Print()
//	{
//		cout << *_ptr << endl;
//	}
//
//private:
//	T* _ptr;
//};
//
//void Test1()
//{
//	Auto_ptr<int> ap1 = Auto_ptr<int>(1);
//	ap1.Print();
//	Auto_ptr<int> ap2(ap1);
//	ap2.Print();
//}
//
//void Test2()
//{
//	Auto_ptr<int> ap1 = Auto_ptr<int>(1);
//	Auto_ptr<int> ap2 = Auto_ptr<int>(2);
//	ap1.Print();
//	ap2 = ap1;
//	ap2.Print();
//}

////////////////////////////////////////////////////////////////////////

//template <class T>
//class Scoped_ptr
//{
//public:
//	Scoped_ptr<T>(const T& x)
//		: _ptr(new T(x))
//	{}
//
//	~Scoped_ptr<T>()
//	{
//		delete _ptr;
//		_ptr = NULL;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	void Print()
//	{
//		cout << *_ptr << endl;
//	}
//private:
//	Scoped_ptr<T>(Scoped_ptr<T>& ap);
//	Scoped_ptr<T>& operator=(Scoped_ptr<T>& ap);
//private:
//	T* _ptr;
//};
//
//void Test1()
//{
//	Scoped_ptr<int> sp1 = Scoped_ptr<int>(1);
//	sp1.Print();
//	Scoped_ptr<int> sp2(sp1);
//	sp2.Print();
//
//	Scoped_ptr<int> sp3 = Scoped_ptr<int>(3);
//	Scoped_ptr<int> sp4 = Scoped_ptr<int>(4);
//	sp3.Print();
//
//	sp3 = sp4;
//
//	sp3.Print();
//
//}

////////////////////////////////////////////////////////////////////////

template <class T>
class Shared_ptr
{
public:
	Shared_ptr<T>(const T& x)
		:_ptr(new T(x))
		,pCount(new int(1))
	{}

	~Shared_ptr<T>()
	{
		if (--(*pCount) == 0)
		{
			delete _ptr;
			delete pCount;
			_ptr = NULL;
			pCount = NULL;
		}
	}

	Shared_ptr<T>(Shared_ptr<T>& sp)
		: _ptr(sp._ptr)
		, pCount(sp.pCount)
	{
		++(*pCount);
	}

	Shared_ptr<T>& operator=(Shared_ptr<T>& sp)
	{
		if (_ptr != sp._ptr)  //最好判断一下这种情况
		{
			if (--(*pCount) == 0)  //减少自己的引用计数
			{
				delete _ptr;
				_ptr = NULL;
			}

			_ptr = sp._ptr;
			pCount = sp.pCount;
			++(*pCount);
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	
	void Print()
	{
		if (*pCount > 0)
			cout << *_ptr << endl;
	}

private:
	T* _ptr;
	int* pCount;
};

void Test1()
{
	Shared_ptr<int> sp1(1);
	sp1.Print();
	Shared_ptr<int> sp2(sp1);
	sp2.Print();
}

void Test2()
{
	Shared_ptr<int> sp1(1);
	Shared_ptr<int> sp2(sp1);
	Shared_ptr<int> sp3(3);
	sp2.Print();
	sp2 = sp3;
	sp2.Print();
}

void Test3()
{
	Shared_ptr<int> sp1(1);
	Shared_ptr<int> sp3(3);
	sp1.Print();
	sp1 = sp3;
	sp1.Print();
}

void main()
{
	//Test1();
	//Test2();
	Test3();



	system("pause");
}