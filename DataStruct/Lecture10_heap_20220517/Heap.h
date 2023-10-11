#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

typedef int HPDataType;
typedef struct Heap
{
	HPDataType* a; //数组
	int size;
	int capacity;
}HP;

void HeapInit(HP* php);

void HeapDestroy(HP* php);

void HeapPrint(HP* php);

void Swap(HPDataType* p1, HPDataType* p2);

//完全二叉树的结点总数N为2^(h-1)<N<2^(h)-1，而AdjustUp和AdjustDown只需要运行高度h次，因此算法复杂度为O(logN)
void AdjustUp(HPDataType* a, int child);//向上调整，用于HeapPush，可以用于构建大小堆

void AdjustDown(HPDataType* a, int size, int parent); //向下调整，用于HeapPop，可以用于构建大小堆

void HeapPush(HP* php, HPDataType x);

void HeapPop(HP* php);

HPDataType HeapTop(HP* php);

bool HeapEmpty(HP* php);

int HeapSize(HP* php);
