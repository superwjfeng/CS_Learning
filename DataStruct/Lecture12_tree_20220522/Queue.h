#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
//前置声明
//typedef struct BinaryTreeNode BTNode;
//typedef BTNode* QDataType;

struct BinaryTreeNode;

typedef struct BinaryTreeNode* QDataType;

typedef struct QueueNode
{
	struct QueueNode* next;
	QDataType data;
}QNode;

typedef struct Queue
{
	//int size;
	QNode* head;
	QNode* tail;  //记录尾结点对于Queue的增加元素很方便，因为Queue只能在队尾增加元素，对于单链表这么实际没有意义，因为还有其他地方的增删查改
}Queue;

void QueueInit(Queue* pq);

void QueueDestroy(Queue* pq);

void QueuePush(Queue* pq, QDataType x);

void QueuePop(Queue* pq);

QDataType QueueFront(Queue* pq);

QDataType QueueBack(Queue* pq);

bool QueueEmpty(Queue* pq);

int QueueSize(Queue* pq);


