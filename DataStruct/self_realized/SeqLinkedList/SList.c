#include "SList.h"

void SLTPrint(SLTNode* phead)
{
	SLTNode* curr = phead;
	while (curr)
	{
		printf("%d->", curr->data);
		curr = curr->next;
	}
	printf("NULL\n");
}

SLTNode* BuySLTNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	assert(newnode);

	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* newnode = BuySLTNode(x);
	if (*pphead == NULL)
		*pphead = newnode;
	else
	{
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = newnode;
	}
}

void SLTPushFront(SLTNode** pphead, SLTDataType x);

void SLTPopBack(SLTNode** pphead);

void SLTPopFront(SLTNode** pphead);

SLTNode* SLTFind(SLTNode* phead, SLTDataType x);

void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);

void SLTErase(SLTNode** pphead, SLTDataType x);

void SLTInsertAfter(SLTNode* pos, SLTDataType x);

void SLTEraseAfter(SLTNode* pos);