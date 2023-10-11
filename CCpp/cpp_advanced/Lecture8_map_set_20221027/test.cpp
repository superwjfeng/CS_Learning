#include <iostream>
#include <set>
#include <map> // 间接包了pair
#include <functional>
#include <string>
using namespace std;

void test_set1()
{
	//	set<int> s = { 1,2,1,6,3,8,5 };
		//s.insert(4);
		//s.insert(2);
		//s.insert(1);

	int a[] = { 1,2,1,6,3,8,5 };
	set<int, greater<int>> s(a, a + sizeof(a) / sizeof(int));
	// 底层是BST，排序+去重
	set<int>::iterator it = s.begin();
	while (it != s.end())
		cout << *it++ << " ";
	cout << endl;
	
}

void test_set2()
{
	int a[] = { 1,2,1,6,3,8,5 };
	multiset<int> s(a, a + sizeof(a) / sizeof(int));
	// 底层是BST，排序
	set<int>::iterator it = s.begin();
	while (it != s.end())
		cout << *it++ << " ";
	cout << endl;
}

void test_map1()
{
	map<string, string> dict;
	pair<string, string> kv1("sort", "排序");
	dict.insert(kv1);
	dict.insert(pair<string, string>("dict", "字典")); // 匿名对象
	dict.insert(make_pair("left", "左边"));
	dict["insert"]; // 返回val& 插入+修改
	dict["insert"] = "插入"; // 返回val& 查找+修改

	auto it = dict.begin();
	while (it != dict.end())
	{
		//cout << (*it).first << "," << (*it).second << endl; // 解引用返回的是pair
		cout << it->first << ":" << it->second << endl; // 解引用返回的是pair，省略了一个箭头
		it++;
	}
	cout << endl;

	for (auto kv : dict)
		cout << kv.first << ":" << kv.second << endl;
	cout << endl;
}

// 统计次数的三种方法
void test_map2()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };

	map<string, int> countMap;
	for (auto& str : arr) 
	{
		map<string, int>::iterator it = countMap.find(str);
		if (it != countMap.end())
			it->second++; //返回的是pair结构体
		else
			countMap.insert(make_pair(str, 1));
	}

	map<string, int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		cout << it->first << ":" << it->second << endl;
		it++;
	}
	cout << endl;
}

void test_map3()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };

	map<string, int> countMap;
	for (auto& str : arr)
	{
		countMap[str]++;
	}

	map<string, int>::iterator it = countMap.begin();
	while (it != countMap.end())
	{
		cout << it->first << ":" << it->second << endl;
		it++;
	}
	cout << endl;
}

int main()
{
	//test_set1();
	//test_set2();
	//test_map1();
	//test_map2();
	test_map3();
	return 0;
}