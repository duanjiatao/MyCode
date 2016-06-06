#include<iostream>

using namespace std;

#include "SeqList.h"


// 顺序表
// 单链表
// 双向链表+双向循环链表


void Test1()
{
	int array[5] = { 1, 2, 3, 4 ,5};
	SeqList s1(array,5);

	s1.Print();
}

void Test2()
{
	SeqList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.Print();

	s1.PopBack();
	s1.Print();

	s1.PushBack(5);
	s1.Print();
}

void Test3()
{
	SeqList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.Print();
	s1.PushFront(0);
	s1.Print();
}

void Test4()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	SeqList s2(s1);
	//s1.Print();
	s2.Print();
}

void Test5()
{
	int array1[5] = { 1, 2, 3, 4, 5 };
	int array2[3] = { 3, 6, 9 };
	SeqList s1(array1, 5);
	SeqList s2(array2, 3);
	s1.Print();
	//cout << s1.Size() << endl;
	s2.Print();
	//cout << s2.Size() << endl;

	s2 = s1;	
	s2.Print();
	cout << s2.Size() << endl;
}

void Test6()
{
	int array[4] = { 1, 2, 4, 5 };
	SeqList s1(array, 4);
	s1.Print();
	//cout << s1.Size() << endl;
	s1.Insert(2, 3);	
	s1.Print();
	s1.Erase(2);
	s1.Print();
	//cout << s1.Size() << endl;
}


void Test7()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	cout << s1.Find(3) << endl;


	s1.Clear();
}

void Test8()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	s1.Print();
	cout << "_size:　" << s1.Size() << endl;
	cout << "_capacity: " << s1.Capacity() << endl;
	s1.Clear();
	cout <<"_size:　"<< s1.Size() << endl;
	cout <<"_capacity: "<< s1.Capacity() << endl;
}

void main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	Test8();
	system("pause");
}
