#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <list>
#include <assert.h>
using namespace std;

void test()
{
	int x = 3;
	int y = 4;
	swap(x, y);
}

void test_string1()
{
	string s1;
	string s2("hello world");
	string s3(s2);
	string s4(s2, 6, 3);
	string s5("hello world", 5);
	string s6(50, 'x');
	string s7 = "hello world"; //隐式类型转换
	//string s4(s2, 6, 10);
	//string s4(s2, 6);
	//string s4(s2, 6, -1);
	//cin >> s1 >> s2; // >> << 经过重载了
	//cout << endl;
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;
	cout << "s5: " << s5 << endl;
	cout << "s6: " << s6 << endl;
	cout << "s7: " << s7 << endl;
}

void test_string2()
{
	string s1("hello world");
	cout << "s1: " << s1 << endl;
	s1[5] = 'x';
	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i]++;
	}
	cout << "s1: " << s1 << endl;

	const string s2("world");
	for (size_t i = 0; i < s2.size(); i++)
	{
//		s2[i]++;
		cout << s2[i] << " ";
	}
	cout << endl;
}

void test_string3()
{
	string s("hello");
	string::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	// 范围 for -- 自动迭代，自动判断结束
	// 依次取s中每个字符，赋值给ch
	for (auto ch : s)
	{
		ch++;
		cout << ch << " ";
	}
	cout << endl;
	cout << s << endl;

	// 范围for的底层其实就是迭代器，即它是迭代器的上层封装

	for (auto& ch : s)
	{
		ch++;
		cout << ch << " ";
	}
}

void test_list()
{
	list<int> lt(10, 1);
	list<int>::iterator lit = lt.begin();
	while (lit != lt.end())
	{
		cout << *lit++ << " ";
	}
	cout << endl;

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 四种迭代器
// iterator/reverse_iterator
// const_iterator/const_reverse_iterator

void PrintString(const string& str)
{
	string::const_iterator it = str.begin();
//	auto it = str.begin(); // auto自动推导
	while (it != str.end())
	{
//		*it = 'x';
		cout << *it++ << " ";
	}
	cout << endl;

	string::const_reverse_iterator rit = str.rbegin();
	while (rit != str.rend())
	{
		cout << *rit++ << " ";
	}
	cout << endl;
}

void test_string4()
{
	string s("hello");
	string::reverse_iterator rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << endl;

	PrintString(s);
}

void test_string5()
{
	string s("hello");
	s.push_back('-');
//	s.push_back('-x'); // 只支持插入一个字符，多个要用append
	s.append("-world");
	cout << s << endl;

	string str("New");
	s += "@"; // operator+=
	s += str;
	cout << s << endl;

	s.append(str.begin(), str.end());
	cout << s << endl;
	s.append(++str.begin(), --str.end());
	cout << s << endl;

	string copy(++s.begin(), --s.end());
	cout << copy << endl;
}

void test_string6()
{
	string s1;
	string s2("11111111");
	cout << s1.max_size() << endl;
	cout << s2.max_size() << endl;

	cout << s1.capacity() << endl; // 其实是16，只是不算入标识字符 \0
	cout << s2.capacity() << endl;
}

void test_string7()
{
	string s;
	// s.reserve(1000); // 提前开好1000 Byte的空间，不会初始化，因此不改变size
	s.resize(1000); // 开空间+初始化，因此还会改变size
	size_t sz = s.capacity();
	cout << sz << endl;
	cout << "making s grow:\n";
	for (int i = 0; i < 100; i++)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed to: " << sz << '\n';
		}
	}
}

void test_string8()
{
	string str("wo lai le");
	string s = "20%";
	int sz = s.size();
	for (size_t i = 0; i < str.size();)
	{
		if (str[i] == ' ')
		{
			str.insert(i, s);
			i += (sz+1);
		}
		else
		{
			i++;
		}
	}
	cout << str << endl;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			str.erase(i, 1);
		}
	}
	cout << str << endl;
}

// 以空间换时间
void test_string9()
{
	string str("wo lai le");
	string s = "20%";
	string newstr;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ')
		{
			newstr += str[i];
		}
		else
		{
			newstr += s;
		}
	}
	cout << newstr << endl;
}

void test_string10()
{
	string filename("Test.cpp");
	//fopen(filename, "r"); // C语言的fopen不能使用cpp中的string类型数据
	FILE* fout = fopen(filename.c_str(), "r");
	assert(fout);
	char ch = fgetc(fout);
	while (ch != EOF)
	{
		cout << ch;
		ch = fgetc(fout);
	}
}

void test_string11()
{
	string filename("Test.cpp");
	cout << filename << endl;
	cout << filename.c_str() << endl;

	filename += '\0';
	filename += "string.cpp";
	cout << filename << endl; // string以对象size为准
	cout << filename.c_str() << endl; // C字符串以\0结尾
	// C语言的字符串中是不能有\0的，否则一系列字符串函数都有问题
	// string对象就不会有这个bug

	//for (char ch = 0; ch < 127; ch++)
	//{
	//	cout << ch << " ";
	//}

	cout << endl;
	cout << "\\0" << endl;
	cout << strlen("\\0") << endl;
	cout << strlen("abc\n") << endl;
	cout << sizeof("abc\\n") << endl;
	cout << strlen("abc\\\x23n") << endl;
	cout << "abc\x31" << endl;
	printf("%zu", -1);
}

void DealUrl(const string& url)
{
	// []://[]
	size_t pos1 = url.find("://");
	if (pos1 == string::npos)
	{
		cout << "Illegal URL" << endl;
		return;
	}
	string protocol = url.substr(0, pos1);
	cout << protocol << endl;

	size_t pos2 = url.find('/', pos1 + 3);
	if (pos2 == string::npos)
	{
		cout << "Illegal Domain" << endl;
		return;
	}
	string domain = url.substr(pos1 + 3, pos2 - pos1 - 3);
	cout << domain << endl;

	string uri = url.substr(pos2 + 1);
	cout << uri << endl;
}


void test_string12()
{
	//string filename("test.cpp");
	//size_t pos = filename.find('.');
	//if (pos != string::npos)
	//{
	//	string suff = filename.substr(pos, filename.size() - pos);
	//	cout << suff << endl;
	//}

	string filename("test.cpp.tar.zip");
	size_t pos = filename.rfind('.');
	if (pos != string::npos)
	{
		string suff = filename.substr(pos, filename.size() - pos);
		cout << suff << endl;
	}

	string url1 = "https://cplusplus.com/reference/string/string/substr/";
	DealUrl(url1);
}

void test_string13()
{
	int ival;
	double dval;
	cin >> ival >> dval;
	string istr = to_string(ival);
	string dstr = to_string(dval);
	cout << istr << endl;
	cout << dstr << endl;

	istr = "9999";
	dstr = "9999.99";
	ival = stoi(istr);
	dval = stod(dstr);
}

void test_string14()
{
	string s0;
	string s1("111111");
	string s2("1111111111111111111111111111111111111111111");
	cout << sizeof(s0) << endl;
	cout << sizeof(s1) << endl;
	cout << sizeof(s2) << endl;
}

#include "string.h"

int main()
{	
//	test_string1();
//	test_string2();
//  test_string3();
//	test_list();
//	test_string4();
	//test_string5();
	//test_string6();
	//test_string7();
	//test_string8();
	//test_string9();
	//test_string10();
	//test_string11();
	//test_string12();
	//test_string13();
	test_string14();

	try
	{
		//wjf::test_string1();
		//wjf::test_string2();
		//wjf::test_string3();
		//wjf::test_string4();
		//wjf::test_string5();
		//wjf::test_string6();
		//wjf::test_string7();
		//wjf::test_string8();
		//wjf::test_string9();
		//wjf::test_string10();
		//wjf::test_string11();
		wjf::test_string12();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}