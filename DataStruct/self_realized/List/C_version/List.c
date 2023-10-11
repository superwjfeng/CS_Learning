#include "List.h"

LTNode* BuyListNode(LTDataType x)
{
    LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
    newnode->prev = NULL;
    newnode->next = NULL;
    newnode->data = x;
    
    return newnode;
}

LTNode* ListInit()
{
    LTNode* phead = BuyListNode(-1); // 不存储有效数据的头结点
    phead->prev = phead; // 头结点的prev和next都指向自己
    phead->next = phead;
    return phead;
}

// 在pos之前插入
void ListInsert(LTNode* pos, LTDataType x)
{
    assert(pos);
    LTNode* newnode = BuyListNode(x);
    LTNode* posPrev = pos->prev;
    pos->prev = newnode;
    posPrev->next = newnode;
    newnode->next = pos;
    newnode->prev = posPrev; 
}

// 删除pos位置的LTNode
void ListErase(LTNode* pos)
{
    assert(pos);
    LTNode* posPrev = pos->prev;
    LTNode* posNext = pos->next;
    posPrev->next = posNext;
    posNext->prev = posPrev;
    free(pos);
}

//// 不复用Insert
//void ListPushBack(LTNode* phead, LTDataType x)
//{
//    assert(phead);
//    LTNode* newnode = BuyListNode(x);
//    LTNode* tail = phead->prev;
//    tail->next = newnode;
//    newnode->prev = tail;
//    newnode->next = phead;
//    phead->prev = newnode;
//}

// 复用Insert
void ListPushBack(LTNode* phead, LTDataType x)
{
    assert(phead);
    ListInsert(phead, x);
}

//// 不复用Insert
//void ListPushFront(LTNode* phead, LTDataType x)
//{
//    assert(phead);
//    LTNode* newnode = BuyListNode(x);
//    LTNode* next = phead->next;
//    newnode->prev = phead;
//    newnode->next = next;
//    phead->next = newnode;
//    next->prev = newnode;
//}

// 复用Insert
void ListPushFront(LTNode* phead, LTDataType x)
{
    assert(phead);
    ListInsert(phead->next, x);
}

bool ListEmpty(LTNode* phead)
{
    assert(phead);
    return phead->next == phead;
}

//// 不复用Erase
//void ListPopBack(LTNode* phead)
//{
//    assert(phead);
//    assert(!ListEmpty(phead));
//    LTNode* tail = phead->prev;
//    LTNode* tailPrev = tail->prev;
//    tailPrev->next = phead;
//    phead->prev = tailPrev;
//    free(tail); 
//}

// 复用Erase
void ListPopBack(LTNode* phead)
{
    assert(phead);
    assert(!ListEmpty(phead));
    ListErase(phead->prev);
}

//// 不复用Erase
//void ListPopFront(LTNode* phead)
//{
//    assert(phead);
//    assert(!ListEmpty(phead));
//    LTNode* del = phead->next;
//    LTNode* next = del->next;
//    del->next = NULL;
//    next->prev = phead;
//    del->prev = NULL;
//    free(del);
//    phead->next = next;
//}

// 复用Erase
void ListPopFront(LTNode* phead)
{
    assert(phead);
    assert(!ListEmpty(phead));
    ListErase(phead->next);
}

void ListPrint(LTNode* phead)
{
    assert(phead);
    LTNode* curr = phead->next;
    while(curr != phead)
    {
        printf("%d->", curr->data);
        curr = curr->next;
    }
    printf("head\n");
}

size_t ListSize(LTNode* phead)
{
    assert(phead);
    LTNode* curr = phead;
    int cnt = 0;
    while (curr != phead)
    {
        cnt++;
        curr = curr->next;
    }
    return cnt;
}

void ListDestory(LTNode* phead)
{
    assert(phead);
    LTNode* curr = phead->next;
    while (curr != phead)
    {
        LTNode* next = curr->next;
        ListErase(curr);
        curr = next;
    }
    free(phead);
    phead = NULL;
}
