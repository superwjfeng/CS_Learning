#include "Stack.h"

// using namespace std; // c++标准库 
// 1.项目中，尽量不要用using namespace std，容易造成重定义
// 2.日常练习可以用
// 3.项目中，指定命名空间访问+展开常用

//using std::cout;
//using std::endl;
//
//int main()
//{
//	std::cout << "hello bit" << std::endl;
//	cout << "hello bit" << endl;
//
//	return 0;
//}

using namespace std;

//int main()
//{
//	int i;
//	double d;
//	cin >> i >> d; // console in 
//	cout << i << endl; // console out
//	cout << d << endl;
//	// 控制格式化输出 宽度、精度等还是用printf比较方便
//
//	return 0;
//}

//// 缺省参数（默认形参）
//void Func(int a = 0)
//{
//	cout << a << endl;
//}
//
//// 全缺省参数
//void TestFunc(int a = 10, int b = 20, int c = 30)
//{
//	cout << "a=" << a << endl;
//	cout << "b=" << b << endl;
//	cout << "c=" << c << endl << endl;
//}
//
//// 半缺省参数
//// 必须从左往右连续缺省，不能间隔
//// void TestFunc2(int a, int b = 20, int c) // 这么写是错的
//void TestFunc2(int a, int b = 20, int c = 30)
//{
//	cout << "a=" << a << endl;
//	cout << "b=" << b << endl;
//	cout << "c=" << c << endl << endl;
//}
//
//// 函数重载需要参数个数或顺序或类型不同，返回值不同不构成重载
//// 函数重载对的意义就是让用的地方很方便，就像用同一个函数一样
//// 实际上自动识别变量类型就是通过函数重载实现的 
//int Add(int left, int right)
//{
//	return left + right;
//}
//
//// double Add(double right, double left) // 形参名顺序不同是没有意义的
//double Add(double left, double right)
//{
//	return left + right;
//}
//
//int main()
//{
//	Func(1);
//	Func(2);
//	Func(3);
//	Func();
//
//	TestFunc();
//	TestFunc(1);
//	TestFunc(1, 2);
//	TestFunc(1, 2, 3);
//
//	struct Stack st1;
//	// 若知道一定会用100哥数据，就可以显示传参数100
//	// 提前开好空间，插入数据避免扩容，因为扩容是有速度损失的
//	StackInit(&st1, 100);
//
//	return 0;
//}

//// 引用
//// 1. 引用在定义时必须初始化 2. 一个引用在定义时必须初始化
//// 3. 一个引用不能引用多个实体
//int main()
//{
//	int a = 0;
//	int& b = a; // 引用为变量取别名，与被引用变量共用同一块空间，不会开辟新空间 
//	cout << &b << endl; // 取地址
//	return 0;
//}

//// 引用的实际作用
//// 1. 做参数 -- 输出型参数、大对象传参，提高效率（引用不开新空间）
//// 2. 做返回值 -- 传值返回：不管是否是static，都生成一个返回对象拷贝作为函数调用返回值 
////                传引用返回：出了函数作用域，返回对象就销毁了。因此一定不能用引用返回，一定要用传值返回，不然结果是未定义的
//					a. 输出型返回对象，调用者可以修改返回对象 b. 减少拷贝，提高效率
//void swap(int& r1, int& r2) // 也可以传指 针
//{
//	int tmp = r1;
//	r1 = r2;
//	r2 = tmp;
//}
//
//// 传引用返回本质是不对的，结果是随机值，是没有保障的
//int& Count()
//{
//	// int n = 0;
//	static int n = 0; // 传引用返回的正确用法，变量放到静态区里不会被销毁 
//	n++;
//	// ...
//	return n;
//}
//
//int main()
//{
//	int a = 0, b = 2;
//	swap(a, b);
//	return 0;
//}

int main()
{
	SL sl;
	SLInit(sl);
	SLPushBack(sl, 1);
	SLPushBack(sl, 2);
	SLPushBack(sl, 3);
	SLPushBack(sl, 4);

	for (int i = 0; i < sl.size; ++i)
	{
		cout << SLAt(sl, i) << " ";
	}

	cout << endl;


	for (int i = 0; i < sl.size; ++i)
	{
		cout << SLAt(sl, i) << " ";
	}
	cout << endl;

	SLAt(sl, 0)++;
	SLAt(sl, 0) = 10;

	for (int i = 0; i < sl.size; ++i)
	{
		cout << SLAt(sl, i) << endl;
	}

	return 0;
}