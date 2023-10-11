#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int LTDataType;
typedef struct ListNode
{
    struct ListNode* prev;
    struct ListNode* next;
    LTDataType data;
}LTNode;

LTNode* BuyListNode(LTDataType x);

LTNode* ListInit();

void ListPushBack(LTNode* phead, LTDataType x);

void ListPushFront(LTNode* pehad, LTDataType x);

bool ListEmpty(LTNode* phead);

void ListPopBack(LTNode* phead);

void ListPopFront(LTNode* phead);

void ListPrint(LTNode* phead);

void ListInsert(LTNode* pos, LTDataType x);

void ListErase(LTNode* pos);

size_t ListSize(LTNode* phead);

void ListDestory(LTNode* phead);
