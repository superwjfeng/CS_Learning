#include "Person.h"

//int main()
//{
//	cout << "address of static size in main: " << &size << endl;
//	cout << "address of age in main: " << &age << endl;
//
//	Person p1; // 类的实例化
//	Person p2;
//	Person p3;
//
//	p1.PrintPersonInfo();
//
//	return 0;
//}

//int a;
//
//class A
//{
//public:
//	void PrintA()
//	{
//		cout << _a << endl;
//	}
//	void func()
//	{
//		cout << "void A::func()" << endl;
//	}
////private:
//	char _a;
//};
//
//int main()
//{
//	int b;
//	printf("%d\n%d", a, b);
//	A* ptr = nullptr;
//	ptr->func();
//	return 0;
//}

class Time
{
public:
	Time()
	{
		cout << "Time()" << endl;
		_hour = 0;
		_minute = 0;
		_second = 0;
	}
private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
public:
	//Date()
	//{
	//	_year = 1;
	//	_month = 0;
	//	_day = 0;
	//}

	//Date(int year, int month, int day)
	//{
	//	_year = year;
	//	_month = month;
	//	_day = day;
	//}

	Date(int year=1, int month=0, int day=0) // 全缺省参数Constructor
	{
		_year = year;
		_month = month;
		_day = day;
	}

	~Date() // Destructor
	{
		// 日期类没有声明需要清理的东西
	}

	void Print()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}
	
private:
	int _year;
	int _month;
	int _day;
	Time _t;
};

typedef int DataType;

class Stack
{
public:
	Stack(int capacity = 4)
	{
		_array = (DataType*)malloc(sizeof(DataType) * capacity);
		if (NULL == _array)
		{
			perror("malloc fail!\n");
			return;
		}
		_size = 0;
		_capacity = capacity;
	}

	void Push(DataType data)
	{
		_array[_size] = data;
		_size++;
	}

private:
	DataType* _array;
	int _size;
	int _capacity;
};

int main()
{
	//Date d1(2022, 9, 15);
	Date d;
	return 0;
}