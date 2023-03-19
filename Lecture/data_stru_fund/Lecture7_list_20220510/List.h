#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int LTDataType;
typedef struct ListNode
{
	struct ListNode* next;
	struct ListNode* prev;
	LTDataType data;
}LTNode;

LTNode* BuyListNode(LTDataType x);

LTNode* ListInit();

void ListPrint(LTNode* phead);

void ListPushBack(LTNode* phead, LTDataType x);

void ListPushFront(LTNode* phead, LTDataType x);

void ListPopBack(LTNode* phead);

bool ListEmpty(LTNode* phead);

void ListPopFront(LTNode* phead);

void ListInsert(LTNode* pos, LTDataType x);

void ListErase(LTNode* pos);

int ListSize(LTNode* phead);

void ListDestroy(LTNode* phead);



