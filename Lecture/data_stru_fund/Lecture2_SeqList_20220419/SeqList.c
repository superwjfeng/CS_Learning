#include "SeqList.h"

//// 这样写是不行的，形参是实参的一份临时拷贝，该函数不会对传入的实参产生影响
//void SLInit(SL s)
//{
//	s.a = NULL;
//	s.size = s.capacity = 0;
//}

void SLInit(SL* ps)
{
	assert(ps); //防御式编程
	ps->a = NULL;
	ps->size = ps->capacity = 0;
}

void SLDestroy(SL* ps)
{
	if (ps->a)
	{
		free(ps->a);
		ps->a = NULL;
		ps->capacity = ps->size = 0;
	}
}

void SLPrint(SL* ps)
{
	assert(ps); 
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

void SLCheckCapacity(SL* ps)
{
	assert(ps);
	//检查容量空间，满了扩容
	if (ps->size == ps->capacity)
	{
		int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity; //一开始先开4个不够再开
		SLDataType* tmp = (SLDataType*)realloc(ps->a, sizeof(SLDataType) * newCapacity);
		if (tmp == NULL)
		{
			perror("realloc");
			exit(-1); //直接终止程序
		}

		ps->a = tmp;
		ps->capacity = newCapacity;
	}
}

void SLPushBack(SL* ps, SLDataType x)
{
	//assert(ps);
	//SLCheckCapacity(ps);

	//ps->a[ps->size] = x;
	//ps->size++;

	SLInsert(ps, ps->size, x);
}

void SLPushFront(SL* ps, SLDataType x)
{
	//assert(ps);
	//SLCheckCapacity(ps);

	//int end = ps->size - 1;
	//while (end >= 0)
	//{   
	//	ps->a[end + 1] = ps->a[end]; //从后往前挪
	//	--end;
	//}

	//ps->a[0] = x;
	//ps->size++;
	SLInsert(ps, 0, x); //SLInsert复用
}

void SLPopBack(SL* ps)
{ 
	//assert(ps);
	////ps->a[ps->size - 1] = 0; //置成多少没有意义，只要size--后最后一位就是无效数据了
	//////温柔检查，数组是否越界
	////if (ps->size == 0)
	////{
	////	printf("SeqList is empty\n");
	////	return;
	////}

	////暴力检查
	//assert(ps->size > 0); //防止删过头
	//ps->size--;
	SLErase(ps, ps->size - 1);
}

void SLPopFront(SL* ps) //头删
{
	//assert(ps);
	//assert(ps->size > 0);
	//int begin = 1;
	//while (begin < ps->size)
	//{
	//	ps->a[begin - 1] = ps->a[begin]; //从前往后挪
	//	++begin;
	//}

	//ps->size--;

	SLErase(ps, 0);
}

void SLInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	//assert(pos >= 0 && pos < ps->size); //保证连续存放
	assert(pos >= 0 && pos <= ps->size); //'='是为了适合尾插的复用
	SLCheckCapacity(ps);

	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		--end; //从后往前挪
	}
	ps->a[pos] = x;
	ps->size++;
}

void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);

	int begin = pos;
	while (begin < ps->size - 1)
	{
		//ps->a[begin - 1] = ps->a[begin];
		ps->a[begin] = ps->a[begin + 1]; //从前往后挪
		++begin;
	}
	
	ps->size--;
}

int SLFind(SL* ps, SLDataType x)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
			return i;
	}

	return -1;
}

void SLModify(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);

	ps->a[pos] = x;

}
