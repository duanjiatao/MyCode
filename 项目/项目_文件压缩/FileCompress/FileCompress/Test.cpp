#include<iostream>
#include<windows.h>
using namespace std;
#include "FileCompress.h"





void main()
{
	size_t begin1 = GetTickCount();
	TestCompress();
	size_t end1 = GetTickCount();
	cout << "compress time: " << (end1 - begin1) / 1000 << endl;


	//size_t begin2 = GetTickCount();
	//TestUncompress();
	//size_t end2 = GetTickCount();
	//cout << "compress time: " << (end2 - begin2) / 1000 << endl;



	

	

	system("pause");
}