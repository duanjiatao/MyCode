#include"ListNode.h"

void main()
{
	//ListNode* List1;
	//ListNode* List2;
	
	//Init_SList(&List1);
	//Init_SList(&List2);

	//PushBack(List1,1);	
	//PushBack(List2,2);
	//PushBack(List1,3);
	//PushBack(List2,4);	
	//PushBack(List1,5);	
	
	
	
	//PrintList(List);

	//PushFront(List,0);
	//PrintList(List1);
	//PrintList(List2);

	//Reverse(List);
	//PrintList(List);

	//Remove(List,1);
	//PrintList(List);

	//ListNode* node = Find(List,1);
	//Insert(node,9);
	//PrintList(List);

	//ListNode* node = Find(List,1);
	//Erase(List,node);
	//PrintList(List);

	//PrintTailToHead(List);
	
	//ListNode* node = Find(List,4);
	//DeleteNode(node);
	//PrintList(List);

	//ListNode* node = Find(List,3);
	//InsertNode(node,9);
	//PrintList(List);

	//ListNode* node = FindMid(List);
	//printf("Mid = %d\n",node->_data);
	//PrintList(List);

	//ListNode* node = Joseph(List,3);
	//PrintList(List); 
	//node->_next = NULL;  //解环
	//printf("last = %d\n",node->_data);

	

	//ListNode* node = MergeList(List1,List2);
	//PrintList(node);

	ListNode* List3;
	Init_SList(&List3);

	PushBack(List3,3);	
	PushBack(List3,1);
	PushBack(List3,2);
	PushBack(List3,5);	
	PushBack(List3,4);
	PushBack(List3,6);
	//PrintList(List3);

	SortList(List3);  
	PrintList(List3);

	ListNode* List4;
	Init_SList(&List4);

	PushBack(List4,3);	
	PushBack(List4,1);
	PushBack(List4,2);
	PushBack(List4,4);
	//PrintList(List4);

	SortList(List4);  
	PrintList(List4);

	//ListNode* node = FindTailK(List,7);
	//if(node != NULL)
	//{
		//printf("K = %d\n",node->_data);
	//}

	//ListNode* node = Find(List3,3);
	//node->_next = List3;  //连成环
	//ListNode* node1 = IsExitsLoop(List3);
	//int n = GetCycleLength(node1);
	//printf("Cycle length = %d\n",n);

	//ListNode* node = Find(List3,3);
	//node->_next = List3;  //连成环
	//ListNode* node1 = IsExitsLoop(List3);
	//ListNode* node2 = GetEnrtyNode(List3,node1);
	//printf("Entry = %d\n",node2->_data);

	ListNode* node1 = Find(List3,6);
	ListNode* node2 = Find(List4,4);
	node2->_next = node1;  //让两个链表相交
	bool bl = CheckCross(List3,List3);
	if(bl)
	{
		printf("相交\n");
		PrintList(List3);
		PrintList(List4);
	}
}