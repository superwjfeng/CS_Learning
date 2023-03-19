#include <iostream>
#include <assert.h>
#include <string>
using namespace std;

class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout << "A():" << this << endl;
	}

	~A()
	{
		cout << "~A():" << this << endl;
	}

private:
	int _a;
};

// 模板参数定义了模板类型，类似函数参数，但函数参数定义了参数对象
// typename后面类型名字T是随便取的，一般是大写字母或者单词首字母大写 T、Ty、K、V，代表了一个模拟类型/虚拟类型
template<typename T>
void Swap(T& left, T& right)
{
	T temp = left;
	left = right;
	right = temp;
}

template<class T>
T* Func(int n)
{
	T* a = new T[n];
	return a;
}

template<typename T1, typename T2>
T1 Add(const T1& left, const T2& right) // 指定了返回为T1时，编译器就可以进行强制类型转化了
{
	return left + right;
}

void TestFuncTemp()
{
	int i = 1, j = 2;
	double x = 1.1, y = 2.2;
	Swap(i, j);
	Swap(x, y);
	printf("%d, %d\n", i, j);
	printf("%f, %f\n", x, y);
	Func<A>(10);
}


// template<typename T>
template<class T> // 上下两种类模板都可以
class Stack
{
public:
	Stack(size_t capacity = 4)
		:_a(nullptr)
		, _capacity(0)
		, _top(0)
	{
		if (capacity > 0)
		{
			_a = new T[capacity];
			_capacity = capacity;
			_top = 0;
		}
	}
	~Stack()
	{
		delete[] _a;
		_a = nullptr;
		_capacity = _top = 0;
	}

	void Push(const T& x)
	{
		if (_top == _capacity)
		{
			// 1、开新空间
			size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
			T* tmp = new T[newCapacity]; // C语言中的内存函数不能用于自定义类型，所以cpp中没有和realloc对标的函数，需要自己来拷贝数据
			if (_a) // 第一次插入 _a可能为空
			{
				// 2、拷贝数据
				memcpy(tmp, _a, sizeof(T) * _top);
				// 3、释放旧空间
				delete[] _a;
			}
			_a = tmp;
			_capacity = newCapacity;
		}
		_a[_top++] = x;
	}

	void Pop()
	{
		assert(_top > 0);
		--_top;
	}

	bool Empty()
	{
		return _top == 0;
	}

	const T& Top()
	{
		assert(_top > 0);
		return _a[_top - 1];
	}
private:
	T* _a;
	int _top;
	int _capacity;
};

void TestClassTemp()
{
	try
	{
		// 类模板都是显式实例化
		// 虽然用了一个类模板，但 Stack<int> 和 Stack<char> 不是一种数据类型
		// 虽然用了一个类模板，但 Stack<int> 和 Stack<char> 不是一种数据类型
		Stack<int> st1;
		Stack<char> st2;
		st1.Push(1);
		st1.Push(2);
		st1.Push(3);
		st1.Push(4);
		st1.Push(5);

		while (!st1.Empty())
		{
			cout << st1.Top() << " ";
			st1.Pop();
		}
		cout << endl;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

void TestString()
{
	char a1[] = "Hello";
	char a2[] = "比特";

	char a3[5] = { -79, -56, -52, -40, 0 };
	char a4[4] = { 65, 95, 66, '\0'};
	cout << a3 << endl;
	char ch = 'a';

}

int main()
{
//	TestClassTemp();
	TestString();
	printf("你好");
	return 0;
}