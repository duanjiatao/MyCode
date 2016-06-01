#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<string.h>

#define MAX 5
typedef int DataType;

typedef struct SeqList
{
	DataType *array;
	size_t size;
	size_t capicity; 
}SeqList;

void InitSeqList(SeqList *pSeq)//初始化
{
	pSeq->array = (DataType*)malloc(sizeof(DataType)*MAX);
	memset(pSeq->array, 0, MAX);
	pSeq->size = 0;
	pSeq->capicity = MAX;
}

void capicity(SeqList *pSeq)//空间不足开辟新空间
{
	DataType *tmp;
	tmp = (DataType*)malloc(sizeof(DataType)*(pSeq->capicity)*2);
	memcpy(tmp,pSeq->array,sizeof(DataType)*(pSeq->capicity));
	free(pSeq->array);
	pSeq->array = tmp;
	pSeq->capicity = (pSeq->capicity) * 2;
}

void PrintSqeList(SeqList *pSeq)//打印数据
{
	assert(pSeq);
	int i;
	for (i = 0; i<(int)(pSeq->size); i++)
	{
	printf("%d  ", (pSeq->array)[i]);
	}
	printf("\n");
}

void PushBack(SeqList *pSeq,DataType x)//尾插
{
	assert(pSeq);
	if(pSeq->size == pSeq->capicity)
	{
		capicity(pSeq);
	}
	(pSeq->array)[pSeq->size] = x;
	pSeq->size++;
}

void RemoveAll(SeqList* pSeq, DataType x)  //删除所有x
{
	assert(pSeq);
	size_t first=0,second=0,count=0;
	if (pSeq->size == 0)
	{
		printf("SeqList is Empty\n");
		return;
	}
	while(second < pSeq->size)
	{
		if(pSeq->array[second] != x)
		{
			pSeq->array[first] = pSeq->array[second];
			first++;
			second++;
			
		}
		else
		{
			second++;
			count++;
		}
	}
	pSeq->size-=count;

	for (size_t i = 0; i<pSeq->size; i++)
	{
		if (pSeq->array[i] == x)
		{
			for (size_t j = i; j<pSeq->size; j++)
			{
				pSeq->array[j] = pSeq->array[j+1];
			}
			pSeq->size--;
		}
	}
}

void BubbleSort(SeqList *pSeq)  //冒泡排序优化算法
{
	assert(pSeq);
    int flag = 1;
    int n = pSeq->size;
    while(flag)
    {
        flag = 0;
        for(int i=1;i<n;i++)
        {
            if(pSeq->array[i-1]>pSeq->array[i])
            {
				DataType temp;
				temp = pSeq->array[i-1];
				pSeq->array[i-1] = pSeq->array[i];
				pSeq->array[i] = temp;
                flag = 1;
            }
        }
        n--;
    }
}

void SelectSort(SeqList* pSeq) //选择排序改进算法：同时选出最大和最小值 
{
	 assert(pSeq);
     size_t i, min, max, left, right;
     DataType temp;
     for (left=0, right=pSeq->size-1; left<right; left++, right--)
     {
         min = left;
         max = right;
         for (i=left; i<=right; i++)
         {
             if (pSeq->array[i] < pSeq->array[min])
             {
                 min = i;
             }
             else if (pSeq->array[i] > pSeq->array[max])
             {
                 max = i;
             }
         }
         
         if (min != left)
         {
             temp = pSeq->array[left];
             pSeq->array[left] = pSeq->array[min];
             pSeq->array[min] = temp;
             
             if (max == left) //最大值最左边,位置发生变化
			 {
                 max = min;
             }
         }    
         
         if (max != right)
         {
             temp = pSeq->array[right];
             pSeq->array[right] = pSeq->array[max];
             pSeq->array[max] = temp;
         }
     }
 }

size_t BinSearch(SeqList* pSeq,DataType x)  //二分查找
{
	DataType Left=0;
	DataType Right=pSeq->size-1;
	DataType Mid;
	while(Left <= Right)
	{
		Mid=Left+(Right-Left)/2;  //可防止越界
		if(pSeq->array[Mid] < x)
		{
			Left = Mid + 1; 
		}
		else if(pSeq->array[Mid] > x)
		{
			Right = Mid - 1;
		}
		else
		{
			return Mid;
		}
	}
	return -1;
} 

int BinSearch2(SeqList* pSeq,size_t start,size_t end,DataType key) //递归实现二分查找
{ 
	int result; 
	int p = (start + end) / 2;
	if(pSeq->array[p] == key || start >= end) 
	{ 
		if (pSeq->array[p] == key) 
		{ 
			result = p;
			return result; 
		}
		else 
		{ 
			result = -1; 
			return result;
		}
	} 
	else
	{ 
		if (pSeq->array[p] > key) 
		{ 
			result = BinSearch2(pSeq, start, p, key); 
		} 
		else 
		{ 
			result = BinSearch2(pSeq, p + 1, end, key);
		} 
		return result; 
	} 
}
