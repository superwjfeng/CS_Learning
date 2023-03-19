#include "SList.h"

void TestSList1()
{
	SLTNode* n1 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n1);
	SLTNode* n2 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n2);
	SLTNode* n3 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n3);
	SLTNode* n4 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n4);
	n1->data = 1;
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = NULL;

	SLTNode* plist = n1;
	SListPrint(plist);

	SListPushBack(&plist, 5);
	SListPushBack(&plist, 6);
	SListPushBack(&plist, 7);
	SListPushBack(&plist, 8);
	SListPushFront(&plist, 10);
	SListPrint(plist);
	//SLTNode* newPlist = SListPushFront(plist, 10);
	//SListPrint(newPlist);
}

//void TestSList2_old()
//{
//	SLTNode* plist = NULL;
//	SListPushBack(plist, 1);
//	SListPushBack(plist, 2);
//	SListPushBack(plist, 3);
//	SListPushBack(plist, 4);
//	SListPrint(plist);
//}

void TestSList2()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);
	SListPushFront(&plist, 0);
	SListPrint(plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPopFront(&plist);
	SListPrint(plist);
}

void TestSList3()
{
	SLTNode* plist = NULL; //当列表里一个节点都没有的时候，头结点的地址就是NULL
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);
	SListPushFront(&plist, 0);
	SListPrint(plist);
	SListPopBack(&plist);
	SListPrint(plist);
	SListPopBack(&plist);
	SListPrint(plist);
	SListPopBack(&plist);
	SListPrint(plist);
	SListPopBack(&plist);
	SListPrint(plist);
	SListPopFront(&plist);
	SListPrint(plist);
	//SListPopFront(&plist);
	//SListPrint(plist);
}

void TestSList4()
{
	SLTNode* plist = NULL;
	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPrint(plist);

	SLTNode* ret = SListFind(plist, 3);
	if (ret)
	{
		printf("Find it\n");
		ret->data = 30;
	}
	SListPrint(plist);

	SLTNode* pos = SListFind(plist, 4);
	if (pos)
	{
		SListInsert(&plist, pos, 40);
	}
	SListPrint(plist);
}

SLTNode* removeElements(SLTNode* head, int val){
	SLTNode* curr = head;
	SLTNode* tail = head;
	head = NULL;
	while (curr)
	{
		if (curr->data == val)
		{
			struct ListNode* del = curr;
			curr = curr->next;
			free(del);
		}
		else
		{// 尾插
			// if (tail == NULL)
			// {// 第一次插入
			//     head = tail = curr;
			// }
			// else
			// {
			tail->next = curr;
			tail = tail->next;
			// }
			curr = curr->next;
		}
	}
	if (tail)
		tail->next = NULL;
	return head;
 }

void TestSList5()
{
	SLTNode* n1 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n1);
	SLTNode* n2 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n2);
	SLTNode* n3 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n3);
	SLTNode* n4 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n4);
	SLTNode* n5 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n5);
	SLTNode* n6 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n6);
	SLTNode* n7 = (SLTNode*)malloc(sizeof(SLTNode));
	assert(n7);
	n1->data = 1;
	n2->data = 2;
	n3->data = 6;
	n4->data = 3;
	n5->data = 4;
	n6->data = 5;
	n7->data = 6;

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = n6;
	n6->next = n7;
	n7->next = NULL;

	SLTNode* head = removeElements(n1, 6);
}

int main()
{
	//TestSList1();
	TestSList5();
	return 0;
}