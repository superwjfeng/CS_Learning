#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#pragma once

#define N 100
typedef int SLDataType;

////静态顺序表
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};

//数据必须从第一个位置开始，连续存储
//静态顺序表不实用，使用动态顺序表
typedef struct SeqList
{
	SLDataType* a; //指向动态数组指针
	int size;
	int capacity;
}SL;

void SLInit(SL* ps);

void SLDestroy(SL* ps);

void SLPrint(SL* ps);


void SLPushBack(SL* ps, SLDataType x); //尾插
void SLPopBack(SL* ps); //尾删
// 顺序表适合尾插尾删，O(1) 效率很高，不适合头插头删，需要挪动数据 O(N)

void SLPushFront(SL* ps, SLDataType x); //头插
void SLPopFront(SL* ps); //头删

void SLCheckCapacity(SL* ps);

void SLInsert(SL* ps, int pos, SLDataType X); //在pos位置插入数据

void SLErase(SL* ps, int pos); //删除pos位置的数据

int SLFind(SL* ps, SLDataType x);

void SLModify(SL* ps, int pos, SLDataType x);
