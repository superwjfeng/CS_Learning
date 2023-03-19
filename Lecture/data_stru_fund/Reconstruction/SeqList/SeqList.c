#include "SeqList.h"

//增删查改
void SLInit(SL* ps)
{
	assert(ps);
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}

void SLDestory(SL* ps)
{
	if (ps->a)
	{
		free(ps->a);
		ps->a = NULL;
		ps->size = ps->capacity = 0;
	}
}

void SLCheckCapacity(SL* ps)
{
	assert(ps);
	if (ps->capacity == ps->size)
	{
		int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		SLDataType* tmp = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * newCapacity);
		if (!tmp)
		{
			perror("realloc");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newCapacity;
	}
}

void SLPrint(SL* ps)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
		printf("%d ", ps->a[i]);
	printf("\n");
}

void SLInsert(SL* ps, int pos, SLDataType x)
{
	SLCheckCapacity(ps);
	assert(pos >= 0 && pos <= ps->size);
	for (int i = ps->size; i >= pos; i--)
		ps->a[i] = ps->a[i - 1];
	ps->a[pos] = x;
	ps->size++;
}

void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	for (int i = pos; i < ps->size; i++)
		ps->a[i - 1] = ps->a[i];
	ps->size--;
}

//void SLPushBack(SL* ps, SLDataType x)
//{
//	SLCheckCapacity(ps);
//	ps->a[ps->size] = x;
//	ps->size++;
//}
//
//void SLPushFront(SL* ps, SLDataType x)
//{
//	SLCheckCapacity(ps);
//	for (int i = ps->size - 1; i >= 0; i--)
//		ps->a[i + 1] = ps->a[i];
//	ps->a[0] = x;
//	ps->size++;
//}
//
//void SLPopBack(SL* ps)
//{
//	assert(ps);
//	assert(ps->size > 0); //防止删过头
//	ps->size--;
//}
//
//void SLPopFront(SL* ps)
//{
//	assert(ps);
//	assert(ps->size > 0);
//	for (int i = 0; i < ps->size; i++)
//		ps->a[i] = ps->a[i + 1];
//	ps->size--;
//}

//对SLInsert()和SLErase()的复用
void SLPushBack(SL* ps, SLDataType x)
{
	SLInsert(ps, ps->size, x);
}

void SLPushFront(SL* ps, SLDataType x)
{
	SLInsert(ps, 0, x);
}

void SLPopBack(SL* ps)
{
	SLErase(ps, ps->size - 1);
}

void SLPopFront(SL* ps)
{
	SLErase(ps, 0);
}

int SLFind(SL* ps, SLDataType x)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
		if (ps->a[i] == x)
			return i;
	return -1;
}

void SLModify(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	ps->a[pos] = x;
}