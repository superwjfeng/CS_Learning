#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <functional>
using namespace std;


//int main() {
//	int x1 = 1;
//	int x2 = { 2 };
//	int x3{ 2 };
//
//	auto x = { 1,2,3,4,5 };
//	cout << typeid(x).name() << endl;
//
//	//cout << &10 << endl;
//	
//	int&& rr1 = 10;
//	return 0;
//}

// const T& x 既能接收左值，又能接收右值；若是 T& x就只能接收左值了
//template<class T>
//void Func(const T& x) {}
//
//int main() {
//	//左值：可以取它的地址
//	int a = 10;
//	//const int b = 20;
//	int* p = &a;
//	*p = 100;
//	
//	//以下的p、b、c、*p都是左值
//	int* p0 = new int(0);
//	int b = 1;
//	const int c = 2;
//	//以下几个是对上面左值的左值引用
//	int*& rp = p;
//	int& rb = b;
//	const int& rc = c;
//	int& pvalue = *p;
//
//	double x = 1.1, y = 2.2;
//
//	//右值：不能取地址
//	10;
//	x + y;
//	fmin(x, y);
//
//	//对右值的右值引用
//	int&& rr1 = 10;
//	double&& rr2 = x + y;
//	double&& rr3 = fmin(x, y);
//
//	//左值引用可以引用右值吗：const的左值引用可以
//	//double& r1 = x + y; //错误
//	const double& r1 = x + y;
//	//右值引用可以引用左值吗：不可以，可以引用move之后的左值
//	//int&& rr5 = b;
//	int&& rr5 = move(b);
//
//
//
//	return 0;
//}

//namespace bit
//{
//	class string
//	{
//	public:
//		typedef char* iterator;
//		iterator begin()
//		{
//			return _str;
//		}
//		iterator end()
//		{
//			return _str + _size;
//		}
//		string(const char* str = "")
//			:_size(strlen(str))
//			, _capacity(_size)
//		{
//			//cout << "string(char* str)" << endl;
//			_str = new char[_capacity + 1];
//			strcpy(_str, str);
//		}
//		// s1.swap(s2)
//		void swap(string& s)
//		{
//			::swap(_str, s._str);
//			::swap(_size, s._size);
//			::swap(_capacity, s._capacity);
//		}
//
//		//// 拷贝构造现代写法
//		//string(const string& s)
//		//	:_str(nullptr)
//		//{
//		//	cout << "string(const string& s) -- 深拷贝" << endl;
//		//	string tmp(s._str);
//		//	swap(tmp);
//		//}
//		//拷贝构造传统写法
//		string(const string& s)
//			:_str(nullptr)
//		{
//			cout << "string(const string& s) -- 深拷贝" << endl;
//			_str = new char[s._capacity + 1];
//			strcpy(_str, s._str);
//			_size = s._size;
//			_capacity = s._capacity;
//		}
//		// 赋值重载
//		string& operator=(const string& s)
//		{
//			cout << "string& operator=(string s) -- 赋值深拷贝" << endl;
//			string tmp(s);
//			swap(tmp);
//			return *this;
//		}
//
//		//// 移动构造
//		//string(string&& s)
//		//	:_str(nullptr)
//		//	, _size(0)
//		//	, _capacity(0)
//		//{
//		//	cout << "string(string&& s) -- 移动构造" << endl;
//		//	swap(s);
//		//}
//		//// 移动赋值
//		//string& operator=(string&& s)
//		//{
//		//	cout << "string& operator=(string&& s) -- 移动赋值" << endl;
//		//	swap(s);
//		//	return *this;
//		//}
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//		char& operator[](size_t pos)
//		{
//			assert(pos < _size);
//			return _str[pos];
//		}
//		void reserve(size_t n)
//		{
//			if (n > _capacity)
//			{
//				char* tmp = new char[n + 1];
//				strcpy(tmp, _str);
//				delete[] _str;
//				_str = tmp;
//				_capacity = n;
//			}
//		}
//		void push_back(char ch)
//		{
//			if (_size >= _capacity)
//			{
//				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
//				reserve(newcapacity);
//			}
//			_str[_size] = ch;
//			++_size;
//			_str[_size] = '\0';
//		}
//		//string operator+=(char ch)
//		string& operator+=(char ch)
//		{
//			push_back(ch);
//			return *this;
//		}
//		const char* c_str() const
//		{
//			return _str;
//		}
//	private:
//		char* _str;
//		size_t _size;
//		size_t _capacity; // 不包含最后做标识的\0
//	};
//}
//
//bit::string to_string(int value)
//{
//	bit::string str;
//	// ...
//	return str;
//}
//
//int main() {
//	bit::string ret;
//	ret = to_string(-3456);
//	return 0;
//}


//void Fun(int& x) { cout << "左值引用" << endl; }
//void Fun(const int& x) { cout << "const 左值引用" << endl; }
//
//void Fun(int&& x) { cout << "右值引用" << endl; }
//void Fun(const int&& x) { cout << "const 右值引用" << endl; }
//
//
//// 万能引用：t既能引用左值，也能引用右值
//// 引用折叠
//template<typename T>
//void PerfectForward(T&& t)
//{
//	// 完美转发：保持t引用对象属性
//	Fun(std::forward<T>(t));
//}
//
////#include"list.h"
//
//int main()
//{
//	PerfectForward(10);           // 右值
//
//	int a;
//	PerfectForward(a);            // 左值
//	PerfectForward(std::move(a)); // 右值
//
//	const int b = 8;
//	PerfectForward(b);		      // const 左值
//	PerfectForward(std::move(b)); // const 右值
//
//	//bit::list<bit::string> lt;
//	//bit::string s1("hello");
//	//lt.push_back(s1);
//
//	//cout << "----------------------------------" << endl;
//
//	////lt.push_back(bit::string("world"));
//	//lt.push_back("world");
//
//	return 0;
//}


//class HeapOnly {
//public:
//	//禁止析构生成，哪里都不能构造类对象
//	~HeapOnly() = delete;
//};
//
//int main() {
//	//自定义类型会调析构，指针不会
//	HeapOnly* ptr = new HeapOnly;
//	return 0;
//}

//template<class ...Args>
//void showList(Args... args) {
//	cout << sizeof...(args) << endl;
//
//	////不能这么用
//	//for (int i = 0; i < sizeof...(args); i++) {
//	//	cout << args[i] << " ";
//	//}
//	//cout << endl;
//}

////0个参数的时候就不能递归调用原函数了，要补充一个只有val参数的函数重载，类似于递归的终结条件
//void ShowList() {
//	cout << endl;
//}
//
////Args... args 代表N个参数包（N >= 0）
//template<class T, class ...Args>
//void ShowList(const T& val, Args... args) {
//	cout << "ShowList(val：" << sizeof...(args) << " -- 参数包：";
//	cout << val << "）" << endl;
//	ShowList(args...);
//}

//template<class T>
//void PrintArg(const T& x) {
//	cout << x << " ";
//}
//
//template<class ...Args>
//void ShowList(Args... args) {
//	int a[] = { (PrintArg(args), 0)... }; //a在这里没有作用，只是为了知道开多大
//	cout << endl;
//}
//
//int main() {
//	string str("hello");
//	//ShowList(1, 'A');
//	ShowList(1, 'A', str);
//
//	return 0;
//}

//int main() {
//	//两个数相加的lambda
//	auto add1 = [](int a, int b)->int {return a + b; };
//	cout << add1(1, 2) << endl;
//
//	//省略返回值
//	auto add2 = [](int a, int b){return a + b; };
//	cout << add2(2, 3) << endl;
//	
//	//交换变量的lambda
//	int x = 0, y = 1;
//	//auto swap1 = [](int& x1, int& x2)->void {int tmp = x1; x1 = x2; x2 = tmp; }; //这样写很难看
//	//swap1(x, y);
//	//cout << x << " " << y << endl;
//	
//	auto swap1 = [](int& x1, int& x2)->void {
//		int tmp = x1;
//		x1 = x2;
//		x2 = tmp;
//	};
//	swap1(x, y);
//	cout << x << " " << y << endl;
//
//	//不传参数交换x和y的lambda，用捕捉列表
//	//默认捕捉的参数不能被修改，要用mutable（此时括号不能被省略）
//	//捕捉采取的是拷贝捕捉，并不是真正的拿了原参数，因此修改之后不会影响外面的，要用传引用捕捉
//	auto swap3 = [&x, &y]()mutable {
//		int tmp = x;
//		x = y;
//		y = tmp;
//	};
//
//	swap3();
//	cout << x << " " << y << endl;
//
//	return 0;
//}

//int main() {
//	int a, b, c, d, e;
//	a = b = c = d = e = 1;
//	auto f1 = [=]() {
//		cout << a << b << c << d << e << endl;
//	};
//
//	f1(); //对匿名函数对象的调用
//
//	return 0;
//}

//class Rate
//{
//public:
//	Rate(double rate) : _rate(rate)
//	{}
//	double operator()(double money, int year)
//	{
//		return money * _rate * year;
//	}
//private:
//	double _rate;
//};
//int main()
//{
//	// 函数对象
//	double rate = 0.49;
//	Rate r1(rate);
//	r1(10000, 2);
//	// lambda
//	auto r2 = [=](double monty, int year)->double {return monty * rate * year;
//	};
//	r2(10000, 2);
//	return 0;
//}


//int f(int  a, int b) {
//	return a + b;
//}
//
//struct Functor {
//public:
//	int operator() (int a, int b) {
//		return a + b;
//	}
//};
//
//class Plus {
//public:
//	static int plusi(int a, int b) {
//		return a + b;
//	}
//	double plusd(double a, double b) {
//		return a + b;
//	}
//};
//
//int main() {
//	std::function<int(int, int)> func1 = f;
//	cout << func1(1, 2) << endl;
//
//	std::function<int(int, int)> func2 = Functor();
//	cout << func2(10, 20) << endl;
//
//	std::function<int(int, int)> func3 = Plus::plusi; //静态成员函数没有this指针
//	cout << func3(100, 200) << endl;
//
	//std::function<double(Plus, double, double)> func4 = &Plus::plusd; //非静态成员函数要取地址，C++规定, Plus相当于是this指针
//	cout << func4(Plus(), 100.11, 200.11) << endl;
//
//	std::function<int(int, int)> func5 = [](int a, int b) {return a + b; };
//	cout << func5(100, 200) << endl;
//
//	return 0;
//}

//class Plus {
//public:
//	static int plusi(int a) {
//		return a;
//	}
//	double plusd(double a) {
//		return a;
//	}
//};
//
//template<class F, class T>
//T useF(F f, T x)
//{
//	static int count = 0;
//	cout << "count:" << ++count << endl;
//	cout << "count:" << &count << endl;
//	return f(x);
//}
//
//double f(double i)
//{
//	return i / 2;
//}
//struct Functor
//{
//	double operator()(double d)
//	{
//		return d / 3;
//	}
//};
//
//int main()
//{
//	// 函数名
//	std::function<double(double)> func1 = f;
//	cout << useF(func1, 11.11) << endl;
//	cout << endl;
//	// 函数对象
//	std::function<double(double)> func2 = Functor();
//	cout << useF(func2, 11.11) << endl;
//	cout << endl;
//	// lamber表达式
//	std::function<double(double)> func3 = [](double d)->double { return d /
//		4; };
//	cout << useF(func3, 11.11) << endl;
//	cout << endl;
//
//	std::function<double(double)> func4 = Plus::plusi;
//	cout << useF(func4, 11.11) << endl;
//	cout << endl;
//	//std::function<double(Plus, double)> func5 = std::bind(&Plus::plusd, Plus(), std::placeholders::_1); //非静态成员函数要取地址，C++规定, Plus相当于是this指针
//	//cout << useF(func5, 11.11);
//	//cout << &func5 << endl;
//	return 0;
//}

class Plus {
public:
	Plus(int x = 2)
		:_x(x)
	{}

	int plusi(int a, int b) {
		return (a + b)*_x;
	}
private:
	int _x;
};


int main()
{
	std::function<int(Plus, int, int)> func3 = &Plus::plusi;
	cout << func3(Plus(), 100, 200) << endl;

	std::function<int(int, int)> func4 = std::bind(&Plus::plusi, Plus(10), \
		std::placeholders::_1, std::placeholders::_2); //绑定参数，相当于
	cout << func4(100, 200) << endl;
	return 0;
}

