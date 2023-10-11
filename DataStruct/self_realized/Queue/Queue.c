#include "Queue.h"

void QueueInit(Queue* pq)
{
    assert(pq);
    pq->head = pq->tail = NULL;
}
                                      
void QueueDestroy(Queue* pq)
{
    assert(pq);
    QNode* curr = pq->head;
    while (curr)
    {
        QNode* next = curr->next;
        free(curr);
        curr = next;
    }
    pq->head = pq->tail = NULL;
}
      
void QueuePush(Queue* pq, QDataType x)
{
    assert(pq);
    QNode* newnode = (QNode*)malloc(sizeof(QNode));
    if (newnode == NULL)
    {
        printf("malloc fail");
        exit(-1);
    }
    newnode->data = x;
    newnode->next = NULL;
    if (pq->tail == NULL)
        pq->head = pq->tail = newnode; // 第一个节点
    else
    {
        pq->tail->next = newnode;
        pq->tail = newnode;
    }
}
      
void QueuePop(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    if (pq->head->next == NULL) // 只有一个节点时，避免野指针
    {
        free(pq->head);
        pq->head = pq->tail = NULL;
    }
    else
    {
        QNode* next = pq->head->next;
        free(pq->head);
        pq->head = next;
    }
}
      
QDataType QueueFront(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->head->data;
}
      
QDataType QueueBack(Queue* pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->tail->data;
}
      
bool QueueEmpty(Queue* pq)
{
    assert(pq);
    return pq->head ==  NULL;
}
      
int QueueSize(Queue* pq)
{
    assert(pq);
    QNode* curr = pq->head;
    int size = 0;
    while (curr)
    {
        size++;
        curr = curr->next;
    }
    return size;
}
