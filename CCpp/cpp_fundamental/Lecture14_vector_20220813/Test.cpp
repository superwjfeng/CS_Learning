#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>

using namespace std;

// 测试封装到std库中，与自己实现的vector进行区分
namespace std
{
	void test_vector1()
	{
		vector<int> v1;
		vector<int> v2(10, 1);
		vector<int> v3(v2);
	}

	void test_vector2()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		cout << v1.max_size() << endl;
		// 遍历 下标+[]
		for (size_t i = 0; i < v1.size(); i++)
			v1[i]++;	
		for (size_t i = 0; i < v1.size(); i++)
			cout << v1[i] << " ";
		cout << endl;
		// 迭代器
		vector<int>::iterator it = v1.begin();
		while (it != v1.end())
		{
			(*it)--;
			cout << *it << " ";
			it++;
		}
		cout << endl;

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void TestVectorExpand()
	{
		size_t sz;
		vector<int> v;
		sz = v.capacity();
		cout << "making v grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			v.push_back(i);
			if (sz != v.capacity())
			{
				sz = v.capacity();
				cout << "capacity changed: " << sz << '\n';
			}
		}
	}

	void test_vector3()
	{
		TestVectorExpand();
	}

	void test_vector4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);
		if (pos != v1.end())
			v1.insert(pos, 30);
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector5()
	{
		vector<int> v1;
		v1.push_back(10);
		v1.push_back(2);
		v1.push_back(32);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(1);
		v1.push_back(9);
		sort(v1.begin(), v1.end());
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
		less<int> ls;
		greater<int> gt;
		//sort(v1.begin(), v1.end(), gt);
		sort(v1.begin(), v1.end(), greater<int>()); // 匿名对象
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		string s("hello65433456");
		sort(s.begin(), s.end(), greater<char>());
		cout << s << endl;

		vector<string> strV;
		string str1("zhangsan");
		strV.push_back(str1); // void push_back (const value_type& val);
		// 传引用是为了避免string类的深拷贝，const是为了可以传const char*类，防止权限放大
		strV.push_back(string("lisi"));
		strV.push_back("wangliu"); // string的构造函数是一个单参数的const cahr*
		// 没有加explicit，支持隐式类型转换

		for (const auto& str : strV) // 传引用，防止深拷贝
			cout << str << endl;
	}

	int removeDuplicates(vector<int>& nums) {
		vector<int>::iterator move = nums.begin();
		vector<int>::iterator stay = nums.begin();
		int sz = 0;
		while (move != nums.end())
		{
			if (*move == *stay)
				move++;
			else
			{
				*(++stay) = *move++;
				sz++;
			}
		}
		return sz + 1;
	}
	
	void test_vector6() // 测试removeDuplicates
	{
		vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };
		int sz = removeDuplicates(nums);
	}

	const char* numToStr[10] = { "", "", "abc", "def", "ghi", "jkl", "mno",
		"pqrs", "tuv", "wxyz" };
	void combine(string digits, int di, vector<string>& retV, string combineStr)
	{ // digits为选中的数字，di为其下标，retV存放返回的可能组合，combineStr
		// 取每个可能的字符串组
		if (di == digits.size())
		{
			retV.push_back(combineStr);
			return;
		}
		int num = digits[di] - '0';
		string str = numToStr[num];
		for (auto ch : str)
			combine(digits, di + 1, retV, combineStr + ch);
		// 这里注意不要写成combineStr+=ch了，因为处于for循环中，combineStr需要重复使用
	}
	vector<string> letterCombinations(string digits) {
		vector<string> v;
		if (digits.empty())
			return v;
		string str;
		combine(digits, 0, v, str);
		return v;
	}
	
	void test_vector7()
	{
		string digits("23");
		vector<string> ret = letterCombinations(digits);
	}

	void test_vector8() {
		vector<bool> v = { true, false, true };
	}
}

#include "vector.h"

int main()
{
	//std::test_vector1();
	//std::test_vector2();
	//std::test_vector3();
	//std::test_vector4();
	//std::test_vector5();
//	printf("%zd\n", sizeof(wjf::vector<int>));
	//std::test_vector6();
	//std::test_vector7();
	std::test_vector8();
	
	//wjf::test_vector1();
	//wjf::test_vector2();
	//wjf::test_vector3();
	//wjf::test_vector4();
	//wjf::test_vector5();
	//wjf::test_vector6();
	//wjf::test_vector7();
	//wjf::test_vector8();
	//wjf::test_vector9();
	//wjf::test_vector10();
	//wjf::test_vector11();
	

	return 0;
}