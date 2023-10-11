#pragma once
#include <iostream>
#include <ostream>
#include <assert.h>

using namespace std;

class Date
{
	// 友元函数 -- 这个函数内部可以使用Date对象访问私有保护成员
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	// 获取某年某月的天数
	// 被频繁调用，所以直接放在类里面定义作为inline
	int GetMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		// 被频繁调用，放到静态区避免栈帧开销
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			return 29;
		}
		else
		{
			return days[month];
		}
	}

	bool CheckDate()
	{
		if (_year >= 1
			&& (_month > 0 && _month< 13)
			&& (_day > 0 && _day <= GetMonthDay(_year, _month)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// 构造函数被频繁调用，所以直接放在类里面定义作为inline
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		assert(CheckDate());
	}

	// Copy constructor
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	void Print() const;
	Date& operator=(const Date& d);
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;
	bool operator>(const Date& d) const;    
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;

	Date& operator+=(int day); // += 是要改变自己的，不能是指为常量
	Date operator+(int day) const; 

	// 分为前置++和后置++
	// 若直接按特性定义，则无法区分
	// 特殊处理，使用函数重载，默认无参为前置，有参为后置
	Date& operator++();
	Date operator++(int); // 传的参数没有效果，仅仅是用来区分

	Date& operator-=(int day);
	Date operator-(int day) const; //日期-数字

	Date& operator--();
	Date operator--(int);

	int operator-(const Date& d) const; // 日期-日期，即日期之间的插值

	// 运算符重载不一定要重载为成员函数
//	void operator<<(ostream& out);

	//Date* operator&();

	//const Date* operator&() const;

private:
	int _year;
	int _month;
	int _day;
};

//void operator<<(ostream& out, const Date& d);

// 流插入重载，能这么写的原因是因为iostream库里已经支持了<<对内置类型的操作
inline ostream& operator<<(ostream& out, const Date& d)
{
	// 返回ostream&，支持连续输出
// 无法访问私有，使用友元
//	out << _year << "-" << _month << "-" << _day << endl;
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}

// 流提取重载
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	assert(d.CheckDate());
	return in;
}

