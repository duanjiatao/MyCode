#include<iostream>
#include<string.h>
#include<string>
#include<assert.h>
using namespace std;

//namespace DeepCopy
//{
	class String
	{
	public:
		String(const char* str = "")
		{
			int len = strlen(str);
			_capacity = len + 1;
			_size = len;
			_str = new char[_capacity];
			strcpy_s(_str, strlen(str) + 1, str);  //注意，此处只能用strcpy_s
		}

		String(const String& s)
			:_str(NULL)
		{
			String tmp(s._str);
			this->_Swap(tmp);
		}

		String& operator=(String s)
		{
			_Swap(s);
			return *this;
		}

		void Display()
		{
			cout << _str << endl;
		}
		void _Swap(String & s)
		{
			swap(_str, s._str);
			swap(_size, s._size);
			swap(_capacity, s._capacity);
		}

		bool operator>(const String& s)
		{
			const char* str1 = _str;
			const char* str2 = s._str;

			while (*str1 && *str2)
			{
				if (*str1 > *str2)
				{
					return true;
				}
				else if (*str1 < *str2)
				{
					return false;
				}
				else
				{
					++str1;
					++str2;
				}
			}

			if (*str1)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		bool operator>=(const String& s)
		{
			return *this > s || *this == s;
		}

		bool operator<(const String& s)
		{
			return !(*this > s || (*this == s));
		}

		bool operator<=(const String& s)
		{
			return *this < s || *this == s;
		}

		bool operator==(const String& s)
		{
			const char* str1 = _str;
			const char* str2 = s._str;

			while (*str1 && *str2)
			{
				if (*str1 == *str2)
				{
					++str1;
					++str2;
				}
				else
				{
					return false;
				}
			}
			if (*str1 || *str2)
			{
				return false;
			}
			else
			{
				return true;
			}
		}


		void PushBack(char ch)
		{
			/*_CheckCapacity(_size + 2);  //注意此处有可能有问题
			_str[_size++] = ch;
			_str[_size] = '\0';*/
			Insert(_size, ch);
		}
		void Insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			_CheckCapacity(_size + 1);
			size_t end = _size;
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;

		}
		void Insert(size_t pos, char* str)
		{
			assert(pos <= _size);
			size_t strSize = strlen(str);
			_CheckCapacity(_size + 1 + strSize);

			size_t end = _size;
			while (end >= pos)
			{
				_str[end + strSize] = _str[end];
				--end;
			}
			while (*str)
			{
				_str[pos++] = *str++;
			}
			_size += strSize;
		}

		char& operator [](size_t index)
		{
			assert(index < _size);
			return _str[index];
		}
		int Find(char ch)
		{
			int begin = 0;
			while (_str[begin] != '\0')
			{
				if (_str[begin] == ch)
				{
					return begin;
				}
				begin++;
			}
			return -1;
		}

		/*int Find(const char* str)
		{
		assert(str && strlen(str) <= _size);
		size_t begin = 0;
		size_t end = 0;
		size_t substr = 0;
		size_t _strlen = _size;
		size_t sublen = strlen(str);

		while (_strlen - begin >= sublen)
		{
		if (_str[end] == str[substr])
		{
		if (substr == sublen - 1)
		{
		return begin;
		}
		++end;
		++substr;
		}
		else
		{
		++begin;
		end = begin;
		substr = 0;
		}
		}
		return -1;
		}
		*/
		int Find(const char* str)
		{

			const char* src = _str;
			const char* sub = str;

			int srcLen = _size;
			int subLen = strlen(sub);

			int srcIndex = 0;

			while (srcIndex <= srcLen - subLen)
			{
				//比较子串
				int i = srcIndex;
				int j = 0;
				while (i < srcLen && j < subLen && src[i] == sub[j])
				{
					++i;
					++j;
				}
				if (j == subLen)
				{
					return srcIndex;
				}
				++srcIndex;
			}
			return -1;
		}




		// bool Erase(size_t pos);
		// bool Erase(size_t pos, size_t n);


	private:
		void _CheckCapacity(size_t size)
		{
			if (size > _capacity)
			{
				int newCapacity = size > 2 * _capacity ? \
				size : 2 * _capacity;
				_str = (char*)realloc(_str, newCapacity);
				_capacity = newCapacity;
			}
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;

	};
	





	void Test1()
	{
		String s1("abcd");
		String s2("abcd");
		//cout << (s1 > s2) << endl;
		//cout << (s1 < s2) << endl;
		cout << (s1 <= s2) << endl;
	}

	void Test2()
	{
		String s1("Hello ld");
		s1.Insert(6, "Wor");
		s1.Display();
	}

	void Test3()
	{
		String s1("Hello World");
		cout << s1[6] << endl;
	}

	void Test4()
	{
		String s1("ABE");
		s1.Insert(2, 'D');
		s1.Display();
		s1.Insert(2, 'C');
		s1.Display();

	}

	void Test5()
	{
		String s1("Hello World");
		cout << s1.Find('a') << endl;
	}

	void Test6()
	{
		String s1("Hello World");
		cout << s1.Find("H") << endl;
	}

	void Test7()
	{
		String s1("Hello ");
		cout << sizeof(s1) << endl;
		s1.Insert(6, "World djt");
		s1.Display();
		cout << sizeof(s1) << endl;
	}

	void Test8()
	{
		string s1;
		cout << sizeof(s1) << endl;

		s1.insert(0, "yyyyyyyyy");
		s1.insert(0, "xxxxxxxxxxxxxxxxxxxxxx");
	}


#include<windows.h>
	void main()
	{
		//int begin = GetTickCount(); 
		//test1();
		//test2();
		//test3();
		Test4();
		//test5();
		//test6();
		//test7();
		//test8();
		//int end = GetTickCount();
		//cout << (begin - end) << endl;
		system("pause");
	}



//}  //命名空间



//namespace std2
//{
//	class String
//	{
//	public:
//		String(const char* str)
//			:_str(new char[strlen(str) + 1])
//			, _pCount(new int(1))
//		{
//			strcpy_s(_str, strlen(str) + 1, str);
//		}
//
//		String(const String& s)
//			:_str(s._str)
//			, _pCount(s._pCount)
//		{
//			++(*_pCount);
//		}
//
//		String& operator=(const String& s)
//		{
//			if (this != &s || _str != s._str)
//			{
//				//释放原对象
//				if (--(*_pCount) == 0)
//				{
//					delete _pCount;
//					delete[] _str;
//				}
//
//				//浅拷贝并增加引用计数
//				_str = s._str;
//				_pCount = s._pCount;
//				++(*_pCount);
//			}
//			return *this;
//		}
//
//
//		~String()
//		{
//			if (--(*_pCount) == 0)
//			{
//				cout << "~String" << endl;
//				delete _pCount;
//				delete[] _str;
//			}
//		}
//
//		char& operator[](size_t pos)  //自己实现
//		{
//			//减
//			return _str[pos];
//		}
//
//	private:
//		char* _str;
//
//		int * _pCount;
//		//static int _count;
//	};
//
//
//
//	void Test1()
//	{
//		String s1("11111111111111111111");
//		String s2(s1);
//		String s3(s2);
//
//		String s4("22222222222222");
//		s1 = s4;
//	}
//}


//namespace std3
//{
//	class String
//	{
//	public:
//		String(const char* str)
//			:_str(new char[strlen(str) + 5])
//		{
//			_str += 4;
//			strcpy_s(_str, strlen(str) + 1, str);
//			_GetRefCount(_str) = 1;
//		}
//
//		String(const String& s)
//			:_str(s._str)
//		{
//			++_GetRefCount(_str);
//		}
//
//		String& operator=(const String& s)
//		{
//			if (_str != s._str)
//			{
//				_Release();
//				
//				_str = s._str;
//				++_GetRefCount(_str);
//			}
//			return *this;
//		}
//
//		~String()
//		{
//			_Release();
//		}
//
//		char& operator[](size_t pos)
//		{
//			//当引用计数大于1，需要完成写时拷贝
//			if (_GetRefCount(_str) > 1)
//			{
//	        	char* tmp = new char[strlen(_str) + 5];
//				tmp += 4;
//				strcpy_s(tmp, strlen(_str) + 1, _str);
//				_GetRefCount(tmp) = 1;
//
//				//一定要放在最后--否则与可能new失败
//				--_GetRefCount(_str); 
//				_str = tmp;
//				
//			}
//			return _str[pos];
//		}
//
//		int Find(const String& s)
//		{
//			cout << "Find(const String& s)" << endl;
//			return -1;
//		}
//
//		/*int Find(const char* _str)
//		{
//			cout << "Find(const char* _str)" << endl;
//			return -1;
//		}*/
//
//		
//
//	private:
//
//		int& _GetRefCount(char* _ptr)
//		{
//			return *((int*)(_ptr - 4));
//		}
//
//		void _Release()
//		{
//			if ((--_GetRefCount(_str)) == 0)
//			{
//				delete[](_str - 4);
//			}
//		}
//
//		
//
//	private:
//		char* _str;
//
//	};
//
//
//	void Test1()
//	{
//		String s1("11111111111111111111");
//		String s2(s1);
//		String s3(s2);
//
//		String s4("22222222222222");
//		s1 = s4;
//	}
//
//	void Test2()
//	{
//		String s1("11111111111111111111");
//		String s2(s1);
//
//		//读时也拷贝
//		cout << s1[0] << endl;
//		
//		//写时拷贝
//		s1[0] = 'x';
//		cout << s1[0] << endl;
//	}
//
//	void Test3()
//	{
//		String s1("xxxxxxxx");
//		String s2(s1);
//		s1.Find("xxxx");
//		s1.Find(s2);
//	}
//}
//#include<windows.h>
//void main()
//{
//	//std3::Test1();
//	//std3::Test2();
//	//string s1("xxxxxxxxxx");
//	//string s2(s1);
//	//std3::Test3();
//	int i = 0;
//	const double& d = i;
//	              // 先产生一个临时变量！临时变量具有常性
//	const int& j = 0;  // 验证
//	system("pause");
//}



