#include "SList.h"

void SListPrint(SLTNode* phead)
{
	SLTNode* curr = phead;
	while (curr)
	{
		printf("%d->", curr->data);
		curr = curr->next;
	}
	printf("NULL\n");
}

SLTNode* BuySListNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	assert(newnode);

	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
////curr是一个局部变量，SListPushBack调用结束后被销毁，所以下面这么写是错误的
////同时
//void SListPushBack(SLTNode* phead, SLTDataType x)
//{
//	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
//	assert(newnode);
//
//	SLTNode* curr = phead;
//	while (curr)
//	{
//		curr = curr->next;
//	}
//	curr = newnode;
//}

////这里的问题是我们的目标是刚开始的链表是没有结点的，其地址为NULL，我们要将*newnode给到plist
////要改变传入的实参指针变量plist，但对形参指针变量phead的改变不能影响plist，因此要传入二级指针
////如果链表中已经有了至少一个结点（带哨兵位的链表），那么传一级指针也能通过tail = tail->next找到尾，并将*newnode给到tail->next
////但哨兵位的使用会带来一系列的问题，且OJ中很多都是不带哨兵位的，因此用二级指针比较好
//void SListPushBack(SLTNode* phead, SLTDataType x)
//{
//	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
//	assert(newnode);
//	newnode->data = x;
//	newnode->next = NULL;
//
//	//一开始结点为空，空指针解引用出错
//	if (phead == NULL)
//		phead = newnode;
//	else
//	{
//		SLTNode* tail = phead;
//		//找尾结点
//		while (tail->next)
//		{
//			tail = tail->next;
//		}
//		//把newnode的地址放到tail->next指针里才算是连接起来了
//		tail->next = newnode;
//	}
//}

//可以用一级指针传参，但要返回一个一级指针
void SListPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead); //所有用二级指针的地方都得检查，因为即使1级指针为空，二级指针也不可能为空
	SLTNode* newnode = BuySListNode(x);
	//一开始一个结点都没有
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//找尾结点
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}     
}
//PushBack结束后newnode指针被销毁，但新创建的node结构体还是存在的，而且原来的tail->next已经
//指向了新的结构体的地址，所以newnode指针被销毁没有影响

//前插时要改变phead，即将phead给newcode，因此仍然要用二级指针
void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* newnode = BuySListNode(x);
	newnode->next = *pphead; //把原来的头结点的地址给新的头结点的next
	*pphead = newnode;  //把新的newnode的地址给到phead
}

//SLTNode* SListPushFront(SLTNode* phead, SLTDataType x)
//{
//	assert(phead);
//	SLTNode* newnode = BuySListNode(x);
//	newnode->next = phead;
//	phead = newnode;
//	return phead;
//}

////下面这么写是错的，顺序反了，如果先free，那么动态开辟出来的结构体中所存储的下一结点的地址就没了
//void SListPopFront(SLTNode** pphead)
//{
//	free(*pphead);
//	*pphead = (*pphead)->next;
//}

void SListPopFront(SLTNode** pphead)
{
	assert(pphead);
	assert(*pphead);
	SLTNode* next = (*pphead)->next;
	free(*pphead);
	*pphead = next;
}

void SListPopBack(SLTNode** pphead)
{
	assert(pphead);
	assert(*pphead); //没有结点
	if ((*pphead)->next == NULL) //只有一个结点
	{
		free(*pphead);
		*pphead = NULL;
	}
	else //还有多个结点
	{
		SLTNode* tailPrev = NULL;
		SLTNode* tail = *pphead;
		while (tail->next)
		{
			tailPrev = tail;
			tail = tail->next;
		}

		free(tail);
		tailPrev->next = NULL;
		
		/*
		SLTNode* tail = *pphead;
		while (tail->next->next)
			tail = tail->next;
		free(tail->next);
		tail->next = NULL;
		*/
	}
}

//查找的附带作用是修改
SLTNode* SListFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* cur = phead;
	while (cur)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

//单链表不适合在pos之前插入，因为需要找前一个位置，可以用双向列表解决
void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	assert(pos); //pos为空时变成尾插了
	assert(pphead);
	if (pos == *pphead) //要插入的是第一个结点，调用头插
		SListPushFront(pphead, x);
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
			prev = prev->next;

		SLTNode* newnode = BuySListNode(x);
		prev->next = newnode;
		newnode->next = pos;
	}
}

// 删除pos位置的node
void SListErase(SLTNode** pphead, SLTNode* pos)
{
	assert(pphead);
	assert(pos);
	if (*pphead == pos)
		SListPopFront(pphead); //删除的是第一个结点
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
			prev = prev->next;

		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

void SListInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);

	//SLTNode* newnode = BuySListNode(x);
	//newnode->next = pos->next;
	//pos->next = newnode;

	//不在乎链接的顺序
	SLTNode* newnode = BuySListNode(x);
	SLTNode* next = pos->next;
	pos->next = newnode;
	newnode->next = next;
}

void SListEraseAfter(SLTNode* pos)
{
	assert(pos);
	assert(pos->next);
	SLTNode* del = pos->next;
	//pos->next = pos->next->next;
	pos->next = del->next;
	free(del);
	del = NULL;
}
