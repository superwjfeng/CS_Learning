#include <iostream>
using namespace std;

//class A
//{
//public:
//    A(int a)
//        :_a1(a)
//        , _a2(_a1)
//    {}
//    void Print() 
//    {
//        cout << _a1 << " " << _a2 << endl;
//    }
//private:
//    int _a2;
//    int _a1;
//};
//
//int main() 
//{
//    A aa(1);
//    aa.Print();
//}


//class Date
//{
//public:
//	Date(int year)
//		:_year(year)
//	{
//		cout << "Constructor" << endl;
//	}
//	Date(const Date& d)
//	{	
//		cout << "Copy Constructor" << endl;
//	}
//private:
//	int _year;
//};
//
//void func(const string& s)
//{
//
//}
//
//int main()
//{
//	Date d1(2022); // 直接调用构造
//	cout << "----------------" << endl;
//	Date d2 = 2022; // 构造+拷贝构造+优化
//
//	string s1("hello");
//	string s2 = "hello";
//	string str("insert");
//	func(str);
//	func("insert");
//
//	return 0;
//}

//class A
//{
//public:
//	A()
//		:_a(3)
//	{ ++_scount; }
//	A(const A& t) { ++_scount; }
//	~A() { --_scount; }
//	static int GetACount() { return _scount; }
////private:
//	static int _scount; // 静态成员变量声明
//	int _a;
//};
//
//// 在类外面定义初始化静态成员变量
//int A::_scount = 0;
//
//int main()
//{
//	A a1;
//	A a2;
//	cout << a1._scount << endl;
//	cout << a2._scount << endl;
//	cout << A::_scount << endl;
//	cout << a1.GetACount() << endl;
//}

//// 设计一个只能在栈上定义对象的类
//class StackOnly
//{
//
//public:
//	static StackOnly CreateObj()
//	{
//		StackOnly so;
//		return so; // 传值返回
//	}
//public:
//	StackOnly(int x = 0, int y= 0)
//		:_x(x)
//		,_y(0)
//	{}
//private:
//	int _x = 0;
//	int _y = 0;
//};
//
//int main()
//{
////	StackOnly so1; // 栈
////	static StackOnly so2; // 静态区
//	StackOnly so3 = StackOnly::CreateObj();
//	return 0;
//}

//// 内部类
//
//class A
//{
//public:
//	class B
//	{
//	public:
//		void FooInner(const A& a)
//		{
//			cout << a._a << endl; // 内部类B是外部类A的友元
//		}
//	private:
//		int _b;
//	};
//	//void FooOuter(const B& b)
//	//{
//	//	cout << b._b << endl; // 外部类A不是内部类B的友元
//	//}
//private:
//	int _a;
//};
//
//int main()
//{
//	cout << sizeof(A) << endl;
//	return 0;
//}



//class W
//{
//public:
//	W(int x = 0)
//	{
//		cout << "W()" << endl;
//	}
//	W(const W& w)
//	{
//		cout << "W(const W& w)" << endl;
//	}
//	W& operator=(const W& w)
//	{
//		cout << "W& operator=(const W& w)" << endl;
//		return *this;
//	}
//	~W()
//	{
//		cout << "~W()" << endl;
//	}
//};
//
//void f1(W w)
//{
//
//}
//
//void f2(const W& w)
//{
//
//}
//
//W f3()
//{
//	W ret;
//	return ret;
//}
//
//
////int main()
////{
////	//W w1;
////	//f1(w1);
////	////f1(W()); // 匿名 本来应该是构造+拷贝构造，编译器优化为直接构造
////	//// 结论：一个连续的表达式步骤中，连续构造一般都会优化为1个构造
////	////cout << endl;
////	////W w2 = 1;
////	//
////	////cout << endl;
////	//
////	//f2(w1);
////	//cout << endl << endl;
////	//f1(W());
////	//W w2 = 1;
////	//cout << endl << endl;
////	f3();
////	return 0;
////}
//
//int main()
//{
//	W ret = f3();
//}

class W
{
public:
	W(int x = 0)
	{
		cout << "W()" << endl;
	}

	W(const W& w)
	{
		cout << "W(const W& w)" << endl;
	}

	W& operator=(const W& w)
	{
		cout << "W& operator=(const W& w)" << endl;
		return *this;
	}

	~W()
	{
		cout << "~W()" << endl;
	}
};

void f1(W w)
{

}

void f2(const W& w)
{

}

W f3()
{
	W ret;
	return ret;
}


W f(W u)
{
	W v(u);
	W w = v;
	return w;
}

int main()
{
	//W w1;
	//f1(w1);
	//cout << endl;
	//W w2;
	//w2 = f3();
	W x;
	W y = f(f(x));
	cout << strlen("\\n") << endl;
	return 0;
}
