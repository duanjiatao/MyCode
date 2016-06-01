#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<iostream>
typedef int DataType;

typedef struct ListNode
{
	DataType _data;
	struct ListNode* _next;
}ListNode;

void Init_SList(ListNode **head)
{
	*head = NULL;
}

ListNode* BuyNode(DataType x)
{
	ListNode* List;
	List = (ListNode*)malloc(sizeof(ListNode));
	List->_data = x;
	List->_next = NULL;
	return List;
}

void PrintList(ListNode* &pHead)
{
	ListNode* PList = pHead;
	while(PList != NULL)
	{
		printf("%d->",PList->_data);
		PList = PList->_next;
    }
	printf("NULL\n");
}

void PushBack(ListNode* &pHead,DataType x)
{
	if(pHead ==  NULL)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode* tail = pHead;
		while(tail->_next != NULL)
		{
			tail = tail->_next;
		}
		tail->_next = BuyNode(x);
	}
}

void PushFront(ListNode* &pHead,DataType x)
{
	if(pHead ==  NULL)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode* New_Head;
		New_Head = BuyNode(x);
		New_Head->_next = pHead;
		pHead = New_Head;
	}
}

void PopBack(ListNode* &pHead)
{
	assert(pHead);
	ListNode* tail = pHead,*pre_tail = NULL;
	while(tail->_next != NULL)
	{
		pre_tail = tail;
		tail = tail->_next;
	}
	pre_tail->_next = NULL;
	free(tail);
	tail = NULL;
}

void PopFront(ListNode* &pHead)
{
	assert(pHead);
	ListNode *head = pHead;
	pHead = pHead->_next;
	free(head);
	head = NULL;
}

ListNode* Find(ListNode* pHead,DataType x)
{
	ListNode* cur = pHead;
	assert(pHead);
	while(cur)
	{
		if(cur->_data == x)
		{
			return cur;
			break;
		}
		cur = cur->_next;
	}
	return NULL;
}

void Insert(ListNode* pos,DataType x)
{
	assert(pos);	
	ListNode* NewNode = BuyNode(x);
	NewNode->_next = pos->_next;
	pos->_next = NewNode;
}

void Erase(ListNode* &pHead,ListNode* pos)
{
	assert(pHead);
	assert(pos);
	ListNode* pre_pos = pHead;
	if(pre_pos == pos)
	{
		PopFront(pHead);  //ע�⣬�˴����봫pHead,��pre_pos�����
	}
	else
	{
		while(pre_pos)
		{
			if(pre_pos->_next == pos)
			{
				pre_pos->_next = pos->_next;
				free(pos);
				pos = NULL;
				break;
			}
			pre_pos = pre_pos->_next;
		}
	}
	
}

void Remove(ListNode* &pHead,DataType x)
{
	assert(pHead);
	ListNode* Del = Find(pHead,x);
	Erase(pHead,Del);
}

void Reverse(ListNode* &pHead)  //��������
{
	assert(pHead);
	
	if(pHead == NULL)
	{
		return;
	}
	ListNode *pre_tail, *tail, *temp;

	ListNode* cur = pHead;
	ListNode* cur_next = cur->_next;
	ListNode* tmp = NULL;

    pre_tail = pHead;
    tail = pHead->_next;
    temp = NULL;

    while (tail != NULL)
	{
        temp = tail->_next;
        tail->_next = pre_tail;
        pre_tail = tail;
        tail = temp;
    }
    pHead->_next = NULL;
    pHead = pre_tail;
}

void PrintTailToHead(ListNode* &pHead)  //��β��ͷ��ӡ������
{
	if(pHead->_next == NULL)
	{
		printf("%d->",pHead->_data);
	}
	else
	{
		PrintTailToHead(pHead->_next);
		printf("%d->",pHead->_data);
	}
}

void DeleteNode(ListNode* pos)  //ɾ����ͷ����ķ�β���
{
	assert(pos);
	ListNode* temp = pos->_next;
	if(temp == NULL)  //�������Ƿ�β�ڵ㣬���Ǽ��ϲ�Ӱ��
	{
		free(pos);
		pos = NULL;
	}
	else
	{
		pos->_next = temp->_next;
		pos->_data = temp->_data;
		free(temp);
		temp = NULL;
	}
}

void InsertNode(ListNode* pos,DataType x)  //��ͷ����ķ�ͷ���ǰ������
{
	assert(pos);
	DataType t;
	ListNode* temp = BuyNode(x);
	temp->_next = pos->_next;
	pos->_next = temp;
	t = pos->_data;  //��������
	pos->_data = temp->_data;
	temp->_data = t;
	pos = temp; 		
}

ListNode* Joseph(ListNode* pHead,int N)  //Լɪ�򻷣������ʣ�µ�һ����
{
	if(pHead == NULL)
	{
		return NULL;
	}
	if(pHead->_next == NULL)
	{
		return pHead;
	}
	ListNode* tail = pHead, *cur = pHead;
	while(tail->_next)  //�����һ���ڵ�
	{
		tail = tail->_next;
	}

	tail->_next = pHead;   //���ɻ�

	int count = 1;
	while(cur->_next != cur)  //��������һ���ڵ㣨����3ɾ��һ����
	{
		if(count == 3)
		{
			ListNode* temp = cur->_next;
			cur->_data = temp->_data;
			cur->_next = temp->_next;
			free(temp);
			temp = NULL;
			count = 1;
		}

		cur = cur->_next;
		count++;
	}
	return cur;
}

void SortList(ListNode* pHead)  //��������
{
	if(pHead == NULL || pHead->_next == NULL)
	{
		return;
	}
	ListNode* prev = pHead,*cur = pHead->_next;
	ListNode* tail = NULL;
	while(tail != pHead)
	{
		prev = pHead;
		cur = pHead->_next;
		while(cur != tail)
		{
			if(prev->_data > cur->_data)  //����
			{

				std::swap(prev->_data, cur->_data);
				/*DataType temp = prev->_data;
				prev->_data = cur->_data;
				cur->_data = temp;*/
			}
			prev = cur;
			cur = prev->_next;
		}
		tail = prev;  //�����������һ���ڵ�
	}
}

ListNode* MergeList(ListNode* pHead1,ListNode* pHead2)  //�ϲ�������������
{
	if(pHead1 == NULL)
	{
		return pHead2;
	}
	if(pHead2 == NULL)
	{
		return pHead1;
	}
	ListNode *cur1 = pHead1,*cur2 = pHead2;
	ListNode* NewHead = NULL;
	ListNode* ret = NULL;
	if(cur1->_data <= cur2->_data)  //��������һ���ڵ�
	{
		NewHead = cur1;
		cur1 = cur1->_next;
	}
	else
	{
		NewHead = cur2;
		cur2 = cur2->_next;
	}
	ret = NewHead;  //�����������ͷ���
	while(cur1 && cur2)
	{
		if(cur1->_data <= cur2->_data)
		{
			NewHead->_next = cur1;
			NewHead = cur1;
			cur1 = cur1->_next;
		}
		if(cur2->_data < cur1->_data)
		{
			NewHead->_next = cur2;
			NewHead = cur2;
			cur2 = cur2->_next;
		}
	}
	if(cur1 == NULL)  //����ֻ����if������while
	{
		NewHead->_next = cur2;
	}
	if(cur2 == NULL)
	{
		NewHead->_next = cur1;
	}
	return ret;
}

ListNode* FindMid(ListNode* pHead)  //�����м���
{
	ListNode* slow = pHead, *fast = pHead;

	// 
	while (fast && fast->_next)
	{
		slow = slow->_next;
		fast = fast->_next->_next;
	}

	return slow;
}

ListNode* FindTailK(ListNode* pHead,int k)  //�ҵ�����K�����
{
	ListNode* slow = pHead,*fast = pHead;
	while(--k)
	{
		if(fast == NULL)
		{
			return NULL;
		}
		fast = fast->_next;	
	}
	while(fast->_next)
	{
		fast = fast->_next;
		slow = slow->_next;
	}
	return slow;
}

ListNode* IsExitsLoop(ListNode* pHead)  //�ж������Ƿ��л�
{
    ListNode *slow = pHead,*fast = pHead;

	ListNode* tail = pHead;
    while( fast && fast->_next) 
    {
        slow = slow->_next;
        fast = fast->_next->_next;
        if(slow == fast)
		{
			return slow;
		}
			
    }
	return NULL;
}

int GetCycleLength(ListNode* meetNode)  //�󻷵ĳ���
{
	ListNode *cur = meetNode;
	int count = 0;
	while(cur->_next != meetNode)
	{
		count++;
		cur = cur->_next;
	}
	return count+1;
}

ListNode* GetEnrtyNode(ListNode* pHead, ListNode* meetNode)  //�󻷵����
{
	while (pHead && meetNode)
	{
		if (pHead == meetNode)
		{
			return pHead;
		}

		pHead = pHead->_next;
		meetNode = meetNode->_next;
	}
	return NULL;
}

bool CheckCross(ListNode* l1, ListNode* l2)  //�ж����������Ƿ��ཻ
{
	ListNode* meetNode1 = IsExitsLoop(l1);
	ListNode* meetNode2 = IsExitsLoop(l2);
	
	if(meetNode1 == NULL && meetNode2 == NULL)  // 1.������
	{
		ListNode* tail1 = l1;
		ListNode* tail2 = l2;
		while (tail1->_next)
		{
			tail1 = tail1->_next;
		}
		while (tail2->_next)
		{
			tail2 = tail2->_next;
		}

		if (tail1 == tail2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	
	if(meetNode1 && meetNode2)  // 2.����
	{
		ListNode* cur = meetNode1;

		while (cur->_next != meetNode1)
		{
			if (cur == meetNode1)
			{
				return true;
			}

			cur = cur->_next;
		}

		return false;
	}

	return false;
}