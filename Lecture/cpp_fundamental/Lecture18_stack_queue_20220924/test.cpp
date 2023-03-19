#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

#include "stack.h"
void test_stack()
{
	//wjf::stack<int, vector<int>> st;
	//wjf::stack<int, list<int>> st;
	wjf::stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}

#include "queue.h"
void test_queue()
{
	//wjf::queue<int, vector<int>> q; // 不支持vector，vector没有pop_front 效率太低
	wjf::queue<int, list<int>> q;
	//wjf::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

#include "PriorityQueue.h"
void test_priority_queue()
{
	wjf::priority_queue<int> pq; // 大堆
	pq.push(3);
	pq.push(1);
	pq.push(2);
	pq.push(5);
	pq.push(0);
	pq.push(1);
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

	int a[] = { 3,2,7,6,0,4,1,9,8,5 };
	//priority_queue<int> heap(a, a + sizeof(a) / sizeof(int)); // 大堆
	wjf::priority_queue<int> heap(a, a + sizeof(a) / sizeof(int)); // 大堆
	//priority_queue<int, vector<int>, greater<int>> heap(a, a + sizeof(a) / sizeof(int)); // 小堆
	while (!heap.empty())
	{
		cout << heap.top() << " ";
		heap.pop();
	}
}

int main()
{
//	test_stack();
//	test_queue();
	test_priority_queue();
	return 0;
}

//// 仿函数/函数对象 -- 类，重载operator()
//namespace wjf
//{
//	template<class T>
//	struct less // 用class也行，但要设置为public
//	{
//		bool operator()(const T& l, const T& r) const
//		{
//			return l < r;
//		}
//	};
//	template<class T>
//	class greater // 用class也行，但要设置为public
//	{
//	public:
//		bool operator()(const T& l, const T& r) const
//		{
//			return l > r;
//		}
//	};
//}
//
//int main()
//{
//	wjf::less<int> lsFunc;
//	cout << lsFunc(1, 2) << endl;
//	cout << lsFunc.operator()(1, 2) << endl; // 本质就是调用运算符重载
//
//	wjf::greater<int> gtFunc;
//	cout << gtFunc(1, 2) << endl;
//	return 0;
//}