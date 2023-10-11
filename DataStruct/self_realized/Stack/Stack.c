#include "Stack.h"

void StackInit(ST* ps)
{
    assert(ps);
    ps->a = NULL;
    ps->top = 0;
    ps->capacity = 0;
}
 
void StackDestroy(ST* ps)
{
    assert(ps);
    free(ps->a);
    ps->a = NULL;
    ps->top = ps->capacity = 0;
}
 
void StackPush(ST* ps, STDataType x)
{
    assert(ps);
    if (ps->top == ps->capacity) // 扩容
    {
        int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
        STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType)*newCapacity);
        if (!tmp)
        {
            printf("realloc fail\n");
            exit(-1);
        }
        ps->a = tmp;
        ps->capacity = newCapacity;
    }
    ps->a[ps->top] = x;
    ps->top++;
}
 
void StackPop(ST* ps)
{
    assert(ps);
    assert(!StackEmpty(ps));
    ps->top--;
}

STDataType StackTop(ST* ps)
{
    assert(ps);
    assert(!StackEmpty(ps));
    return ps->a[ps->top - 1];
}

bool StackEmpty(ST* ps)
{
    assert(ps);
    return ps->top == 0;
}

int StackSize(ST* ps)
{
    assert(ps);
    return ps->top;
}

