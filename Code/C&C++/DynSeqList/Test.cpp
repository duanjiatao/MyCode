#include"DynSeqList.h"


void main()
{
	SeqList Seq;
	InitSeqList(&Seq);
	PushBack(&Seq,4);
	PushBack(&Seq,1);
	PushBack(&Seq,4);
	PushBack(&Seq,5);
	PushBack(&Seq,2);
	PushBack(&Seq,4);
	PushBack(&Seq,3);
	PrintSqeList(&Seq);
	//SelectSort(&Seq);
	BubbleSort(&Seq);
	PrintSqeList(&Seq);
	RemoveAll(&Seq,4);
	printf("%d\n",BinSearch2(&Seq,0,Seq.size,4));
	//PrintSqeList(&Seq);
	//printf("size = %d\n",Seq.size);


}
