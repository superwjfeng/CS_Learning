#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define N 10
typedef int STDataType;
typedef struct Stack
{
    STDataType* a;
    int top;
    int capacity;
}ST;

void StackInit(ST* ps);

void StackDestroy(ST* ps);

void StackPush(ST* ps, STDataType x);

void StackPop(ST* ps);

STDataType StackTop(ST* ps);

bool StackEmpty(ST* ps);

int StackSize(ST* ps);

// 栈没有打印或遍历，这是由栈的性质所决定的
// 若要进行打印或遍历，就相当于把栈清空了

