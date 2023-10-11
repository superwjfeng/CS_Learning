#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

void SListPrint(SLTNode* phead);

SLTNode* BuySListNode(SLTDataType x);

void SListPushBack(SLTNode** pphead, SLTDataType x);

void SListPushFront(SLTNode** pphead, SLTDataType x);
//SLTNode* SListPushFront(SLTNode* phead, SLTDataType x);

void SListPopBack(SLTNode** pphead);

void SListPopFront(SLTNode** pphead);

SLTNode* SListFind(SLTNode* phead, SLTDataType x);

//在pos位置之前插入
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);
//删除pos位置的值
void SListErase(SLTNode** pphead, SLTDataType x);

//单链表在pos位置之后插入x
void SListInsertAfter(SLTNode* pos, SLTDataType x);

//单链表在pos位置之后删除x
void SListEraseAfter(SLTNode* pos);
