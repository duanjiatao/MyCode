#include<iostream>
#include<cassert>
#include"Stack.h"
#include"Queue.h"
#include"QueueByTwoStack.h"
using namespace std;


void Test1()
{
	Stack<int> s1;
  	s1.Display();
	int a[3] = { 1, 2, 3 };
	Stack<int> s2(a, 3);
	s2.Display();
}

void Test2()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	//s1.Display();
	Stack<int> s2(s1);
	//s2.Display();

	int a[3] = { 1, 2, 3 };
	Stack<int> s3(a, 3);
	s3.Display();

	s3 = s1;
	s3.Display();
}

void Test3()
{
	Stack<string> s1;
	s1.Push("D");
	s1.Push("J");
	s1.Push("T");
	//s1.Display();
}

void Test4()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	Queue<int> q2(q1);
	
	q1.Diaplay();
	q2.Diaplay();
}

void Test5()
{
	
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Diaplay();

	Queue<int> q2;
	q2.Push(4);
	q2.Push(5);
	q2.Push(6);
	q2.Diaplay();

	q2 = q1;
	q2.Diaplay();

	q2.Pop();
	q2.Diaplay();
}


void Test6()
{
	Stack<int> s1;
	Stack<int> s2;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);

	QueueByStack<int> Q1(s1, s2);
	Q1.Diaplay();

	Q1.Pop();
	Q1.Diaplay();

	Q1.Push(8);
	Q1.Diaplay();

}

void Test7()
{
	Stack<int> s1;
	Stack<int> s2;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s2.Push(4);
	s2.Push(5);
	s2.Push(6);

	QueueByStack<int> Q1(s1, s2);
	Q1.Diaplay();

	QueueByStack<int> Q2(Q1);
	Q2.Diaplay();

}

void Test8()
{
	Stack<int> s1;
	Stack<int> s2;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s2.Push(4);
	s2.Push(5);
	s2.Push(6);
	QueueByStack<int> Q1(s1, s2);
	//Q1.Diaplay();
	Q1.Push(0);
	Q1.Pop();
	Q1.Pop();
	Q1.Pop();
	Q1.Diaplay();

	cout << Q1.Back() << endl;
	cout << Q1.Front() << endl;



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