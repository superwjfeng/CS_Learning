#include <iostream>
#include <array>
#include <queue>
#include "../Lecture18_stack_queue_20220924/PriorityQueue.h"
using namespace std;


//#define N 100
namespace wjf
{
	template<class T, size_t N = 10>
	class array
	{
	public:
	private:
		T _a[N];
	};

	//int main()
	//{
	//	wjf::array<int> a0;
	//	wjf::array<int, 100> a1;
	//	wjf::array<double, 1000> a2;
	//
	//	return 0;
	//}

	struct Date
	{
	public:
		Date(int year, int month, int day)
			:_year(year)
			, _month(month)
			, _day(day)
		{}

		bool operator>(const Date& d) const
		{
			if ((_year > d._year)
				|| (_year == d._year && _month > d._month)
				|| (_year == d._year && _month > d._month && _day > d._year))
				return true;
			else
				return false;
		}

		bool operator<(const Date& d) const
		{
			if ((_year < d._year)
				|| (_year == d._year && _month < d._month)
				|| (_year == d._year && _month < d._month && _day < d._year))
				return true;
			else
				return false;
		}
		int _year;
		int _month;
		int _day;
	};

	// 函数模板
	template<typename T>
	bool Greater(T left, T right)
	{
		return left > right;
	}

	// 特化 Specilization -- 针对某些类型进行特殊化处理
	// 若输入的参数是指针，就不会进行实例化，而是直接进入下面的特化
	template<>
	bool Greater<Date*>(Date* left, Date* right)
	{
		return *left > *right;
	}

	// 类模板
	template<class T>
	struct greater
	{
		bool operator()(const T& x1, const T& x2) const
		{
			return x1 > x2;
		}
	};

	template<>
	struct greater<Date*>
	{
		bool operator()(Date* p1, Date* p2) const
		{
			return *p1 > *p2;
		}
	};

}
using wjf::Date;

int main()
{
	cout << wjf::Greater(1, 2) << endl; // 可以比较，结果正确
	Date d1(2022, 7, 7);
	Date d2(2022, 7, 8);
	cout << wjf::Greater(d1, d2) << endl; // 可以比较，结果正确
	Date* p1 = &d1;
	Date* p2 = &d2;
	cout << wjf::Greater(p1, p2) << endl; // 可以比较，结果错误

	wjf::greater<Date> greaterFunc1;
	cout << greaterFunc1(d1, d2) << endl;

	wjf::greater<Date*> greaterFunc2;
	cout << greaterFunc2(p1, p2)  << endl;
	
	cout << endl;

	priority_queue<Date, vector<Date>, std::greater<Date>> dq1;
	dq1.push(Date(2022, 9, 28));
	dq1.push(Date(2022, 9, 25));
	dq1.push(Date(2022, 9, 28));
	dq1.push(Date(2022, 9, 29));

	while (!dq1.empty())
	{
		const Date& top = dq1.top();
		cout << top._year << "/" << top._month << "/" << top._day << endl;
		dq1.pop();
	}
	cout << endl;


	std::priority_queue<Date*, vector<Date*>, std::greater<Date*>> dq2;
	dq2.push(new Date(2022, 9, 28));
	dq2.push(new Date(2022, 9, 25));
	dq2.push(new Date(2022, 9, 28));
	dq2.push(new Date(2022, 9, 29));

	while (!dq2.empty())
	{
		const Date* top = dq2.top();
		cout << top->_year << "/" << top->_month << "/" << top->_day << endl;
		dq2.pop();
	}

	return 0;
}

