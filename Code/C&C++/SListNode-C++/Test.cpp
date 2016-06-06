#include<iostream>

using namespace std;

#include"SlistNode.h"

void Test1()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.PushFront(0);
	s1.Print();
}

void Test2()
{
	Slist s1;
	s1.PushFront(3);
	s1.PushFront(2);
	s1.PushFront(1);
	s1.Print();
	Slist s2(s1);
	s2.Print();

	Slist s3;
	s3.PushBack(5);
	s3.PushBack(6);
	s3.PushBack(7);
	s3.Print();
	s3 = s2;
	s3.Print();
	s2.Print();
}
void Test3()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.PushFront(0);
	s1.Print();
	s1.PopBack();
	s1.PopBack();
	s1.Print();
	s1.PopFront();
	s1.PopFront();
	s1.PopFront();
	s1.Print();
	s1.PopFront();
	s1.Print();

}

void Test4()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3); 
	s1.PushBack(5);
	s1.Print();
	SlistNode* cur = s1.Find(3);
	s1.Insert(cur, 4);
	s1.Print();
}

void Test5()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.Print();
	//SlistNode* cur = s1.Find(1);
	//s1.Erase(cur);
	s1.Reverse();
	s1.Print();
	s1.PrintTailToHead();
}

void Test6()
{
	Slist s1;
	s1.PushBack(3);
	s1.PushBack(6);
	s1.PushBack(4);
	s1.PushBack(7);
	s1.PushBack(9);
	s1.PushBack(2);
	s1.PushBack(1);
	s1.PushBack(0);
	s1.PushBack(5);
	s1.PushBack(8);
	s1.Print();
	s1.SortList();
	s1.Print();
}

void Test7()
{
	Slist s1;
	s1.PushBack(0);
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.PushBack(6);
	s1.PushBack(7);
	s1.PushBack(8);
	s1.PushBack(9);
	s1.Print();

	cout << s1.FindTailK(1)->_data << endl;
	cout << s1.FindTailK(2)->_data << endl;
	cout << s1.FindTailK(3)->_data << endl;
	cout << s1.FindTailK(4)->_data << endl;
	cout << s1.FindTailK(5)->_data << endl;
	cout << s1.FindTailK(6)->_data << endl;
	cout << s1.FindTailK(7)->_data << endl;
	cout << s1.FindTailK(8)->_data << endl;
	cout << s1.FindTailK(9)->_data << endl;
	cout << s1.FindTailK(10)->_data << endl;

}

void main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	Test7();



	system("pause");
}