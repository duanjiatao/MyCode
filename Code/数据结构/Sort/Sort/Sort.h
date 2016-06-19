#pragma once
#include<iostream>
#include<cassert>
using namespace std;

void BubbleSort(int* a, size_t n)  //冒泡排序优化版
{
	assert(a);
	bool flag = true;
	for (int i = 0; i < n - 1 && flag; ++i)
	{
		flag = false;
		for (int j = 1; j < n - i; ++j)
		{
			if (a[j - 1] > a[j])
			{
				std::swap(a[j - 1], a[j]);
				flag = true;
			}
		}
	}
}

void SelectSort(int* a, size_t n)  //选择排序优化版
{
	assert(a);

	for (int left = 0, right = n - 1; left < right; ++left, --right)
	{
		int min = left;
		int max = right;

		for (int i = left; i <= right; ++i)
		{
			if (a[i] < a[min])
				min = i;
			else if (a[i] > a[max])
				max = i;
		}

		if (min != left)
		{
			std::swap(a[min], a[left]);

			if (max == left)
			{
				max = min;
			}
		}
		if (max != right)
		{
			std::swap(a[max], a[right]);
		}

	}
}

void InsertSort(int* a, size_t n)  //直接插入排序
{
	assert(a);
	for (int i = 1; i < n; ++i)
	{
		int tmp = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > tmp)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = tmp;
	}
}

void ShellSort(int* a, size_t n)  //希尔排序
{
	assert(a);
	int gap = n;
	while (gap != 1)
	{
		gap = gap / 3 + 1;

		for (int i = gap; i < n; ++i)
		{
			int tmp = a[i];
			int j = i - gap;
			while (j >= 0 && a[j] > tmp)
			{
				a[j + gap] = a[j];
				j -= gap;
			}
			a[j + gap] = tmp;
		}
	}
}

void AdjustDown(int* a, size_t size, size_t root)
{
	assert(a);

	int child = root * 2 + 1;
	while (child < size)  //此处有一个 bug
	{
		if (child+1 < size && a[child + 1] > a[child])
		{
			++child;
		}
		if (a[child] > a[root])
		{
			std::swap(a[child], a[root]);
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a, size_t n)
{
	assert(a);
	for (int i = (n-2)/2; i >=0 ; --i)
	{
		AdjustDown(a, n, i);  //建（大）堆
	}

	for (int i = n - 1; i > 0; --i)  //这样写比较好
	{
		std::swap(a[0], a[i]);
		AdjustDown(a, i - 1, 0);
	}

	//for (int i = 0; i < n; ++i)
	//{
	//	std::swap(a[0], a[n-1-i]);
	//	AdjustDown(a, n-i-1, 0);  //注意这里（第二个参数）传的是元素的个数
	//	                          //，不是下标，已经被坑一次！
	//}
}

//int Partition(int* a, int left, int right)
//{
//	assert(a);
//	int key = a[right];
//	int begin = left;
//	int end = right - 1;
//	while (begin < end)
//	{
//		while (begin < end && a[begin] <= key)
//		{
//			++begin;
//		}
//		while (begin < end && a[end] >= key)
//		{
//			--end;
//		}
//
//		std::swap(a[begin], a[end]);
//	}
//
//	if (a[begin] > key)  // 大于key再交换
//	{
//		std::swap(a[begin], a[right]);
//		return begin;
//	}
//	else
//	{
//		return right;
//	}
//
//}

//这种简单但不容易理解，上面那种比较直观
int Partition(int* a, int left, int right)
{
	assert(a);

	int base = a[left];

	while (left < right)
	{
		while (left < right && a[right] >= base)  //注意这里一定要有等于
			--right;							  //否则会有死循环

		a[left] = a[right];

		while (left < right && a[left] <= base)
			++left;

		a[right] = a[left];
	}

	a[left] = base;
	return left;
}

void QuickSort(int* a, int left, int right)
{
	assert(a);

	if (left < right)
	{
		int pivotloc = Partition(a, left, right);
		QuickSort(a, left, pivotloc-1);
		QuickSort(a, pivotloc+1, right);
	}
}

#include<stack>
void QuickSortNoRe(int* a, int left, int right)  //快排非递归
{
	assert(a);
	if (left >= right)
		return;

	stack<int> st;
	st.push(right);
	st.push(left);
	while (!st.empty())
	{
		int _left = st.top();
		st.pop();
		int _right = st.top();
		st.pop();
		int mid = Partition(a, _left, _right);

		if (_left < mid - 1)
		{
			st.push(mid - 1);
			st.push(_left);
		}
		if (mid + 1 < _right)
		{
			st.push(_right);
			st.push(mid + 1);
		}
	}
}

void _MergeSort(int* src, int* dst, int begin, int end)
{
	assert(src);

	int mid = begin + (end-begin)/2;
	if (begin < end)
	{
		_MergeSort(src, dst, begin, mid);
		_MergeSort(src, dst, mid+1, end);
	}

	int begin1 = begin; 
	int end1 = mid;
	int begin2 = mid + 1; 
	int end2 = end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (src[begin1] <= src[begin2])
		{
			dst[index++] = src[begin1++];
		}
		else
		{
			dst[index++] = src[begin2++];
		}
	}
	while (begin2 <= end2)
	{
		dst[index++] = src[begin2++];
	}
	while (begin1 <= end1)
	{
		dst[index++] = src[begin1++];
	}

	int i = begin;
	while (begin <= end)  // 必须将合并后的序列写回src！
	{
		src[begin++] = dst[i++];
	}

}

void MergeSort(int* a,size_t n)  //归并排序
{
	assert(a);
	int* tmp = new int[n];
	int left = 0;
	int right = n - 1;
	if (left < right)
	{
		_MergeSort(a, tmp, left, right);
	}

	delete[] tmp;
}

void Print(int* a, size_t n)
{
	assert(a);
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void CountSort(int* a, size_t n)  //计数排序
{
	assert(a);
	int min = a[0];
	int max = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > max)
			max = a[i];
		else if (a[i] < min)
			min = a[i];
	}

	int countNum = max - min + 1;
	int* countArray = new int[countNum];
	memset(countArray, 0, sizeof(int)*(countNum));
	for (int i = 0; i < n; ++i)
	{
		++countArray[a[i] - min];
	}

	int index = 0;
	for (int i = 0; i < countNum; ++i)  //写回数组
	{
		while (countArray[i]--)
		{
			a[index++] = i + min;
		}
	}

	delete[] countArray;
}

int GetMaxBit(int* a, size_t n)
{
	assert(a);

	int BitNum = 1;
	int tmpData = 10;
	for (int i = 0; i < n; ++i)
	{
		while (tmpData <= a[i])
		{
			++BitNum;
			tmpData *= 10;
		}
	}
	return BitNum;
}

void RadixSort(int* a, size_t n)  //基数排序
{
	assert(a);
	
	int maxBit = GetMaxBit(a, n);
	int digit = 1;
	int* tmp = new int[n];
	int countBit[10];  //计数
	int startBit[10];  //起始位置
	for (int i = 1; i <= maxBit; ++i)
	{
		memset(countBit, 0, sizeof(int)* 10);
		for (int i = 0; i < n; ++i)
		{
			int bit = (a[i]/digit)%10;  //先各位，在十位百位……
			++countBit[bit];
		}

		memset(startBit, 0, sizeof(int)* 10);
		startBit[0] = 0;
		for (int i = 1; i < 10; ++i)
		{
			startBit[i] = startBit[i - 1] + countBit[i - 1];
		}

		for (int i = 0; i < n; ++i)  //存入临时数组
		{
			int index = startBit[(a[i]/digit)%10]++;
			tmp[index] = a[i];
		}

		for (int i = 0; i < n; ++i)  //写回原数组
		{
			a[i] = tmp[i];
		}

		digit *= 10;
	}
	
	delete[] tmp;
}

void TestBubbleSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	BubbleSort(a, n);
	Print(a, n);
}

void TestInsertSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	InsertSort(a, n);
	Print(a, n);
}

void TestShellSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	ShellSort(a, n);
	Print(a, n);
}

void TestHeapSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	HeapSort(a, n);
	Print(a, n);
}

void TestQuickSort()
{
	//int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int a[] = { 9, 6,5, 3,3, 0, 7, 4, 1, 8, 5, 2 };

	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	QuickSort(a, 0, n-1);
	Print(a, n);
}

void TestQuickSortNoRe()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	QuickSortNoRe(a, 0, n - 1);
	Print(a, n);
}

void TestMergeSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	MergeSort(a, n);
	Print(a, n);
}

void TestCountSort()
{
	int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int n = sizeof(a)/sizeof(int);
	Print(a, n);
	CountSort(a, n);
	Print(a, n);
}

void TestRadixSort()
{
	//int a[] = { 9, 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	int a[] = {31,51,12,82,43,33,84,24,15,65,86,36,17,67,48,58,79,29};
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	RadixSort(a, n);
	Print(a, n);
}

void TestSelectSort()
{
	int a[] = { 9, 6, 3, 2, 7, 4, 1, 8, 5, 0 };
	int n = sizeof(a) / sizeof(int);
	Print(a, n);
	SelectSort(a, n);
	Print(a, n);
}