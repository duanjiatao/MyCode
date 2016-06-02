#include"TwoWayList.h"

void Test()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);

	l1.Print();

	List l2(l1);
	l2.Print();
}

void Test1()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.Print();

	List l2;
	l2.PushBack(4);
	l2.PushBack(5);
	l2.PushBack(6);
	
	l2.Print();

	l2 = l1;
	l2.Print();

}

void Test2()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.Print();
	l1.PopBack();
	l1.Print();
	l1.PopFront();
	l1.Print();
}

void Test3()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.Print();

	ListNode* pos1 = l1.Find(3);
	l1.Insert(pos1, 4);
	l1.Print();

}

void main()
{	
	//Test();
	//Test1();
	//Test2();
	Test3();
}