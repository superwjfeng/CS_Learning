#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

typedef int DataType;

class Date
{
public:
	int GetMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		// 被频繁调用，放到静态区避免栈帧开销
		if (month == 2
			&& (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			return 29;
		}
		else
		{
			return days[month];
		}
		return days[month];
	}

	Date(int year = 1, int month = 0, int day = 0) // 全缺省参数Constructor
	{
		_year = year;
		_month = month;
		_day = day;
	}

	~Date() // 不需要显式写Destructor，默认生成的就够用，但是默认的也没有做什么事情
	{
		// 日期类没有声明需要清理的东西
	}

	Date(const Date& d)
	{
		//cout << "Date(Date& d) " << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	void Print()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}

	//int GetYear()
	//{
	//	return _year;
	//}

	bool operator==(const Date& d) // 引用传参效率高
	// 参数少一个是因为左参数是this指针
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			++_month;
			if (_month == 13)
			{
				_month = 1;
				_year++;
			}
		}
		return (*this);
	}

	Date operator+(int day)
	{
		Date ret(*this);
		ret._day += day;
		while (ret._day > GetMonthDay(ret._year, ret._month))
		{
			ret._day -= GetMonthDay(ret._year, ret._month);
			++ret._month;
			if (ret._month == 13)
			{
				ret._month = 1;
				ret._year++;
			}
		}
		return ret;
	}

private:
	int _year;
	int _month;
	int _day;
};

//bool operator==(const Date& d1, const Date& d2) // 引用传参效率高
//{
//	return d1._year == d2._year
//		&& d1._month == d2._month
//		&& d1._day == d2._day;
//}

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

	~Stack()
	{
		cout << "~Stack()->" << _array << endl;
		free(_array);
		_size = _capacity = 0;
		_array = nullptr;
	}

private:
	DataType* _array;
	int _size;
	int _capacity;
};

class MyQueue
{
public:
	void Push(int x){}

	// 不需要写析构，默认生成的就可以用
	// 默认生成的调用Stack自定义结构的析构函数
private:
	size_t _size = 0;
	Stack _st1;
	Stack _st2;
};

void get1(Date d){}

void get2(Date& d){}

int main()
{
	Date d1(2022, 7, 23);
	Date d2(2022, 7, 24);
	cout << (d1 == d2) << endl;
	cout << d1.operator==(d2) << endl;
	d1 + 50;
//	cout << operator==(d1, d2) << endl; // 类外显式转换成函数调用
//	get1(d1);
//	get2(d1);

//	Date d2(d1); // 类对象的拷贝
//	Date d3 = d1;
	return 0;
}