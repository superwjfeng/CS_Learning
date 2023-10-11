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
	//不用写单独的BuyNode，因为BuyNode是用于在任意地方插入新节点的，而队列中只有队尾可以插入
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}

	newnode->data = x;
	newnode->next = NULL;
	if (pq->tail == NULL)
	{
		pq->head = pq->tail = newnode;
	}
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
	
	//只有一个结点时，避免野指针
	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL; 
	}
	//多个结点
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
	return pq->head == NULL;
}

int QueueSize(Queue* pq)
{
	assert(pq);
	QNode* curr = pq->head;
	int size = 0;
	while (curr)
	{
		++size;
		curr = curr->next;
	}
	return size;
}