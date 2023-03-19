#include "Date.h"

// class A
//{
//public:
//	A(int a = 0)
//	{
//      _a = a;
//		cout << "A(int a = 0)->" <<_a<< endl;
//	}
//
//	~A()
//	{
//		cout << "~A()->" <<_a<<endl;
//	}
//private:
//	int _a;
//};
//
//A aa3(3);
//
//void f()
//{
//	static int i = 0;
//	static A aa0(0);
//	A aa1(1);
//	A aa2(2);
//	static A aa4(4);
//}
//
//// 构造顺序：3 0 1 2 4 1 2
//// 析构顺序：~2 ~1 ~2 ~1 ~4 ~0 ~3
//int main()
//{
//	f();
//	cout << endl << endl;
//	f();
//
//	return 0;
//}

//class A
//{
//public:
//	A(int a = 0)
//	{
//		_a = a;
//		cout << "A(int a = 0)->" << _a << endl;
//	}
//
//	// A aa2(aa1);
//	A(const A& aa)
//	{
//		_a = aa._a;
//		cout << "A(const A& aa)->" << _a << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()->" << _a << endl;
//	}
//private:
//	int _a;
//};
//
//void func1(A aa){}
//
//void func2(A& aa){}
//
//A func3()
//{
//	static A aa(3);
//	return aa;
//}
//
//A& func4()
//{
//	static A aa(4);
//	return aa;
//}
//
//int main()
//{
//	A aa1(1);
////	func1(aa1);
////	func2(aa1);
////	func3();
////	cout << endl << endl;
//	func4();
//	return 0;
//}

void TestDate1()
{
	Date d1(2022, 7, 24);
	Date d2(d1);

	Date d3(2022, 8, 24);
	d2 = d1 = d3;

	int i = 0, j = 1, k = 2;
	k = i = j = 10;
}

void TestDate2()
{
	Date d1(2022, 7, 24);
	Date d2(2022, 7, 25);
	Date d3(2022, 7, 26);

	cout << (d1 < d2) << endl;
	cout << (d1 < d3) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 > d3) << endl;
}

void TestDate3()
{
	Date d1(2022, 7, 24);
	(d1 + 4).Print();
	
	(d1 + 40).Print(); // 跨月

	(d1 + 400).Print(); //跨年

	(d1 + 4000).Print(); // 跨闰年
}

void TestDate4()
{
	Date d1(2022, 7, 25);
	Date d2(2022, 7, 25);
	Date d3(2023, 2, 15);
	(d1 - 4).Print();

	(d1 - 40).Print(); // 跨月

	(d1 - 400).Print(); //跨年

	(d1 - 4000).Print(); // 跨闰年
	
	cout << (d2 - d3) << endl;
	cout << (d3 - d2) << endl;
}

void TestDate5()
{
	// Wrong date assertion
	Date d1(2022, 7, 32);
	Date d2(2022, 2, 29);
}

void Menu()
{
	const char* WeekDay2Str[] = { "Mon", "Tue", "Wed", "Thur", "Fri", "Sat", "Sun" };
	Date d1, d2;
	int day = 0;
	int option = 0;
	do {
		cout << "*******************************" << endl;
		cout << " 1、日期加/减天数 2、日期减日期" << endl;
		cout << " 3、日期->周几   -1、退出" << endl;
		cout << "*******************************" << endl;

		cout << "请选择：";
		cin >> option;
		if (option == 1)
		{
			cout << "请依次输入日期及天数(减天数就输入负数)：";
			cin >> d1 >> day;
			cout << "日期加减天数后的日期：" << d1 + day << endl;
		}
		else if (option == 2)
		{
			cout << "请依次输入两个日期：";
			cin >> d1 >> d2;
			cout << "相差的天数：" << d1 - d2 << endl;
		}
		else if (option == 3)
		{
			cout << "请输入日期：";
			cin >> d1;
			Date start(1582, 10, 15); // 格里高利历的第一天为周五
			int n = d1 - start;
			int weekDay = 4;
			weekDay += n;
			cout << WeekDay2Str[weekDay % 7 + 1] << endl;

		}
		else
		{
			cout << "无此选项，请重新选择" << endl;
		}
	} while (option != -1);
}

void TestDate6()
{
	Date d1(2022, 7, 25);
	Date d2(2022, 7, 26);
	cout << d1 << d2;
	//d1.operator<<(cout);
	//d1 << cout; // << 的左操作数是d1，右操作数是cout，意义不合适，做操作数一定是this，解决不了
	cin >> d1 >> d2;
	cout << d1 << d2;
}

void TestDate7()
{
	Date d1(2022, 7, 25);
	const Date d2(2022, 7, 26);
	
	d1.Print();
//	d2.Print(); // 编译报错，权限放大
	d1 < d2;
//	d2 < d1; // 编译报错，权限放大
}

int main()
{
	//TestDate6();
	Menu();
	return 0;
}