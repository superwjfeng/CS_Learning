#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a; //动态开辟内存，malloc返回的是开辟出来的内存的指针
	int size;
	int capacity;
}SL;

void SLInit(SL* ps);

void SLCheckCapacity(SL* ps);

void SLPrint(SL* ps);

void SLDestory(SL* ps);

void SLInsert(SL* ps, int pos, SLDataType x);

void SLErase(SL* ps, int pos);

void SLPushBack(SL* ps, SLDataType x);
void SLPushFront(SL* ps, SLDataType x);
void SLPopBack(SL* ps);
void SLPopFront(SL* ps);

int SLFind(SL* ps, SLDataType x);

void SLModify(SL* ps, int pos, SLDataType x);



