#include "Date.h"

void Date::Print() const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

Date& Date::operator=(const Date& d)
{
	// this出了类域还存在
	if (this != &d) // 避免自己给自己赋值
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this; // 返回this指向的值为了支持连续赋值 d2 = d1 = d3
}

// 任何一个类，只需要写一个 "=", ">"和"==" 或者 "=", "<"和"==" 重载
// 剩下的比较运算符的重载都可以进行复用
bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

bool Date::operator>(const Date& d) const
{
	if (_year > d._year)
	{
		 return true;
	}
	else if (_year == d._year && _month > d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day)
	{
		return true;
	}
	else
	{
		return false;
	}

	//if ((_year > d._year)
	//	|| (_year == d._year && _month > d._month)
	//	|| (_year == d._year && _month == d._month && _day > d._day))
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

bool Date::operator>=(const Date& d) const
{
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d) const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
	return !(*this > d);
}

// 用+=复用+
Date& Date::operator+=(int day)
{
	// 要改变自身，所以可以直接对自身操作，采用传引用返回

	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}

Date Date::operator+(int day) const
{
	// 因为不改变自身，所以不能直接对*this操作，而是要对其拷贝操作
	// 而拷贝构造所产生的临时变量在栈帧销毁后也被销毁了，所以只能传值返回，不能传引用，否则会引起野指针问题
	// Date ret(*this); // 拷贝构造
	Date tmp = *this; // 注意这里也是拷贝构造，两个已经存在的值才是赋值。两种写法等价
	tmp += day; // 用 += 复用
	return tmp; // 传值拷贝构造
}

//// 用+复用+=
//// 缺点是拷贝次数过多
//Date Date::operator+(int day)
//{
//	Date ret(*this);
//	ret._day += day;
//	while (ret._day > GetMonthDay(ret._year, ret._month))
//	{
//		ret._day -= GetMonthDay(ret._year, ret._month);
//		++ret._month;
//		if (ret._month == 13)
//		{
//			ret._year++;
//			ret._month = 1;
//		}
//	}
//	return ret;
//}
//
//Date& Date::operator+=(int day)
//{
//	*this = *this + day;
//	return *this;
//}

// 前置++
Date& Date::operator++()
{
	*this += 1;
	return *this;
}

// 后置++
Date Date::operator++(int)
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}

// 用-=来复用-
Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month < 1)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

Date Date::operator-(int day) const
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}

int Date::operator-(const Date& d) const
{
	int flag = 1;
	Date max = *this;
	Date min = d;

	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}

	return n * flag;
}

//void Date::operator<<(ostream& out)
//{
//	out << _year << "-" << _month << "-" << _day << endl;
//}

//ostream& operator<<(ostream& out, const Date& d)
//{
//	// 返回ostream&，支持连续输出
//// 无法访问私有，使用友元
////	out << _year << "-" << _month << "-" << _day << endl;
//	out << d._year << "-" << d._month << "-" << d._day << endl;
//	return out;
//}


//Date* Date::operator&()
//{
//	return nullptr;
//}
//
//const Date* Date::operator&() const
//{
//	return nullptr;
//}

