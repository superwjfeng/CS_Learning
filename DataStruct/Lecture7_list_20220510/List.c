#include "List.h"

LTNode* BuyListNode(LTDataType x)
{
	LTNode* node = (LTNode*)malloc(sizeof(LTNode));
	if (node == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	node->data = x;
	node->next = NULL;
	node->prev = NULL;
	return node;
}


//void ListInit(LTNode** pphead)
//{
//	*pphead = BuyListNode(-1);
//	(*pphead)->next = *pphead;
//	(*pphead)->prev = *pphead;
//}

LTNode* ListInit()
{
	LTNode* phead = BuyListNode(-1);
	phead->next = phead;
	phead->prev = phead;
	return phead;
}

void ListPrint(LTNode* phead)
{
	assert(phead);
	LTNode* curr = phead->next;
	while (curr != phead)
	{
		printf("%d ", curr->data);
		curr = curr->next;
	}
	printf("\n");
}
  
void ListPushBack(LTNode* phead, LTDataType x)
{
	assert(phead);
	//LTNode* newnode = BuyListNode(x);
	//LTNode* tail = phead->prev;
	//tail->next = newnode;
	//newnode->prev = tail;
	//newnode->next = phead;
	//phead->prev = newnode;
	ListInsert(phead, x);
}

void ListPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	//LTNode* newnode = BuyListNode(x);
	//LTNode* next = phead->next;
	//phead->next = newnode;
	//newnode->next = next;
	//newnode->prev = phead;
	//next->prev = newnode; 

	///* 若不创建中间变量next，则要严格按照顺序写
	//phead->next->prev = newnode;
	//newnode->next = phead->next;
	//phead->next = newnode; //这句要放在后面
	//newnode->prev = phead;
	//*/

	ListInsert(phead->next, x);
}

bool ListEmpty(LTNode* phead)
{
	assert(phead);  
	return phead->next == phead;
}

void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(!ListEmpty(phead)); //判断最后只剩一个头结点的时候
	//LTNode* tail = phead->prev;
	//LTNode* tailPrev = tail->prev;
	//phead->prev = tailPrev;
	//tailPrev->next = phead;
	//free(tail);
	ListErase(phead->prev);
}

void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(!ListEmpty(phead));
	ListErase(phead->next);
}

void ListInsert(LTNode* pos, LTDataType x)
{
	assert(pos);
	LTNode* prev = pos->prev;
	LTNode* newnode = BuyListNode(x);
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}

void ListErase(LTNode* pos)
{
	assert(pos);
	LTNode* prev = pos->prev;
	LTNode* next = pos->next;

	prev->next = next;
	next->prev = prev;
	free(pos);
}

//当链表中存储的数据是int型时，可以使用哨兵位存储数据个数，但如果存的是其他数据，那么就可能会出现溢出等问题
int ListSize(LTNode* phead)
{
	assert(phead);
	LTNode* curr = phead;
	int size = 0;
	while (curr!=phead)
	{
		++size;
		curr = curr->next;
	}
	return size;
}

void ListDestroy(LTNode* phead)
{
	assert(phead);
	LTNode* curr = phead->next;
	int size = 0;
	while (curr != phead)
	{
		LTNode* next = curr->next;
		ListErase(curr);
		curr = next;
	}
	free(phead);
	phead = NULL;
}
