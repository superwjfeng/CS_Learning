#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

#define N 10
typedef int STDataType;
//typedef struct Stack
//{
//	STDataType a[N];
//	int top; //标识栈顶位置
//}ST;
typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}ST;

void StackInit(ST* ps);

void StackDestory(ST* ps);

void StackPush(ST* ps, STDataType x); //压栈

void StackPop(ST* ps); //出栈

STDataType StackTop(ST* ps);

bool StackEmpty(ST* ps);

int StackSize(ST* ps);

//栈没有打印或遍历，这是由栈的性质的，如果要打印或遍历，相当于把栈清空了
