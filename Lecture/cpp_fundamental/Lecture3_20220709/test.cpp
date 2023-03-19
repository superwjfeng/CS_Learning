#include <iostream>
using namespace std;

//int main()
//{
//	int a = 10;
//	int& b = a;
//	int c = 100;
//	int d = 200;
//
//	b = c;
//	d = b; 
//	return 0;
// }

//int main()
//{
//	int a = 10;
//	int& b = a; // 权限平移
//	cout << typeid(a).name() << endl;
//	cout << typeid(b).name() << endl;
//	
//	const int c = 20;
//	cout << typeid(c).name() << endl;
//	// int& d = c; // 权限放大，这么写是错误
//	const int d = c;
//
//	int e = 30;
//	const int& f = e; // 权限缩小
//
//	int ii = 1;
//	double dd = ii; // 隐式类型转换
//	
//	// double dd = (double)ii;
//	// cout << typeid(ii).name() << endl;
//	// 强制转换只是创建了一个double的临时变量，不改变原变量ii
//
//
//	// 和整体提升过程一样 在转换过程中产生的是具有常性的const double 临时变量
//	// double& rdd = ii; // 因此这么写是错误的，本质原因是权限缩小
//	const double& rdd = ii;
//	
//	const int& x = 10; // 可以引用常量
//
//	// const引用具有很强的接受度，因为其权限比较小
//
//	return 0;
//}

//void func1(int n)
//{
//
//}
//
//// 若使用引用传参，函数内若不改变n，那么建议尽量用const 引用传参
//void func2(const int& n)
//{
//
//}
//
//int main()
//{
//	int a = 10;
//	const int b = 20;
//	func1(a);
//	func1(b); // 权限放大缩小涉及指针和引用，因为这两个是可以修改原变量的，形参没有这个问题
//	func1(30);
//
//	func2(a);
//	func2(b); // 权限放大
//	func2(30);
//	func2(1.11);
//	double d = 2.22;
//	func2(d);
//
//	return 0;
//}

int main()
{
	// 语法的角度，ra没有开空间
	// 底层实现角度，引用底层仍是用指针实现的，也有开空间
	// 但理解还是要用语法角度理解
	int a = 10;
	int& ra = a;
	ra = 20;

	// 语法的角度，pa开了4或者8 Byte空间
	int* pa = &a;
	*pa = 20;
	
	return 0;
}