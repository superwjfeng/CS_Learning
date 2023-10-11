#pragma once

struct QueueNode
{
	QueueNode* next;
	int val;
};

// 类域

class Queue
{
public:
	inline  void Init();
	void Push(int x);
	void Pop();
private:
	QueueNode* head;
	QueueNode* tail;
};
