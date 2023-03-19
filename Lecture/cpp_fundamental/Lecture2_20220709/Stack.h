#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

struct Stack
{
	int* _a;
	int _top;
	int _capacity;
};

// 缺省参数不能在函数声明和定义中同时出现
// 分离定义时：以声明为准
void StackInit(struct Stack* ps, int capacity = 4);

typedef struct SeqList
{
	int* a;
	int size;
	int capacity;
}SL;

void SLInit(SL& s, int capacity = 4);

void SLPushBack(SL& s, int x);

// 修改顺序表数据的函数

void SLModify(SL& s, int pos, int x);

int& SLAt(SL& s, int pos);

