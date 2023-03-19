#include <iostream>
#define ADD(a,b) ((a)+(b))
using namespace std;

//int main()
//{
//	// 宏使用的特殊场景
//	ADD(1, 2);
//
//	if (ADD(1, 2))
//	{
//		;
//	}
//
//	ADD(1, 2) * 3;
//
//	int a = 1, b = 2;
//	ADD(a | b, a & b); // 加号优先级高于 | &
//}

//inline int Add(int a, int b)
//{
//	//printf("int Add(%d, %d\n)", a, b);
//	return a + b;
//}
//
//inline void func(int a, int b)
//{
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//	cout << a + b << endl;
//}
//
//int main()
//{
//	func(1, 2);
//	Add(1, 2);
//}

//// auto用于判断变量类型
//int TestAuto()
//{
//	return 10;
//}
//
//int main()
//{
//	int a = 10;
//	auto b = a;
//	auto c = 'a';
//	auto d = TestAuto();
//	cout << typeid(b).name() << endl;
//	cout << typeid(c).name() << endl;
//	cout << typeid(d).name() << endl;
//
//	int x = 10;
//	auto a = &x; // int*
//	auto* b = &x; // int* 强调是指针
//	auto& c = x; // int 强调c是一个引用
//	cout << typeid(a).name() << endl;
//	cout << typeid(b).name() << endl;
//	cout << typeid(c).name() << endl;
//	return 0;
//
//}

//#include <map>
//#include <string>
//
//int main()
//{
//	int a[] = { 1,2,3,4,5,6 };
//	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
//	{
//		cout << a[i] << " ";
//	}
//
//	cout << endl;
//
//	// 范围for
//	// 自动依次取a的数据，赋值给e
//	// 自动迭代，自动判断结束
//	for (auto e : a)
//	{
//		cout << e << " ";
//	}
//
//	cout << endl;
//
//	// 类型比较长的时候，auto自动推导
//	std::map<std::string, std::string> dict;
//	std::map<std::string, std::string>::iterator it1 = dict.begin();
//	auto it2 = dict.begin();
//
//	return 0;
//}

//void f(int)
//{
//	cout << "f(int)" << endl;
//}
//
//void f(int*)
//{
//	cout << "f(int*)" << endl;
//}
//
//int main()
//{
//	int* p = NULL;
//	f(0);
//	f(NULL);
//	f(p);
//	return 0;
//}

//// C++ 兼容C struct 语法
//struct Stack
//{
//	int* a;
//	int top;
//	int capacity;
//};
//
//void StackInit(struct Stack* ps);
//void StackPush(struct Stack* ps, int x);
//void StackPop(struct Stack* ps);


//// C++ 同时将struct 升级成了类，但是C++中定义类还是更喜欢使用class
//// 成员变量
//// 方法：成员函数
//struct Stack
//{
//	void Init()
//	{
//		a = 0;
//		top = capacity = 0;
//	}
//
//	void Push(int x)
//	{
//		// ...
//	}
//
//	void Pop()
//	{
//		// ...
//	}
//
//	int* a;
//	int top;
//	int capacity;
//};

class Stack
{
public: // 访问限定符，在遇到下一个限定符之前都有效 
	void Init()
	{
		a = 0;
		top = capacity = 0;
	}

	void Push(int x)
	{
		// ...
	}

	void Pop()
	{
		// ...
	}

	int Top()
	{
		return a[top-1];
	}

private:
	int* a;
	int top;
	int capacity;
};

//typedef struct ListNode
//{
//	struct ListNode* next; // C写法，此处不能改成 LTNode* next;
//	int val;
//}LTNode;

// C++写法
struct ListNode
{
	ListNode* next; 
	int val;
}LTNode;

struct QueueNode
{
	QueueNode* next;
	int val;
};

class Queue
{
public:
	void Init();
	void Push(int x);
	void Pop();

private:
	QueueNode* haed;
	QueueNode* tail;
};

int main()
{
	//struct Stack st1; // 兼容C中的结构定义方法
	//Stack st2; // C++中的类名就是类型名

	Stack st;
	st.Init();
	st.Push(1);
	st.Push(2);
	st.Push(3);
	
	// 私有属性访问报错
	//st.a = nullptr; 

	// cout << st.a[st.top] << endl; // 错误的写法
	cout << st.Top() << endl;
	return 0;
}
