#include "Stack.h"

void StackInit(struct Stack* ps, int capacity)
{
	ps->_a = (int*)malloc(sizeof(int) * capacity);
	// ... 
	ps->_top = 0;
	ps->_capacity = capacity;
}

void SLInit(SL& s, int capacity = 4)
{
	s.a = (int*)malloc(sizeof(int) * capacity);
	assert(s.a);
	s.size = 0;
	s.capacity = capacity;
}

void SLPushBack(SL& s, int x)
{
	if (s.size == s.capacity)
	{
		//...
	}
	s.a[s.size++] = x;
}

int& SLAt(SL& s, int pos)
{
	assert(pos >= 0 && pos <= s.size);

	return s.a[pos];
}