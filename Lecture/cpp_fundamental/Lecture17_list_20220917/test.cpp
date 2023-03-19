#include <iostream>
#include <list>
using namespace std;

void list_test1()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	list<int>::iterator it = lt.begin();
	while (it != lt.end())
		cout << *it++ << " ";
	cout << endl;

	for (auto e : lt)
		cout << e << " ";
	cout << endl;

	cout << endl;

	list<int>::reverse_iterator rit = lt.rbegin();
	while (rit != lt.rend())
		cout << *rit++ << " ";
	cout << endl;

	for (auto e : lt)
		cout << e << " ";
	cout << endl;
}

void list_test2()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	auto pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end())
	{
		// pos 不会失效
		lt.insert(pos, 30);
		lt.insert(pos, 20);
		*pos = 100;
	}
	for (auto e : lt)
		cout << e << " ";
	cout << endl;

	auto posErase = find(lt.begin(), lt.end(), 4);
	if (posErase != lt.end())
	{
		// pos 会失效
		lt.erase(posErase);
		cout << *pos << endl;
	}
	for (auto e : lt)
		cout << e << " ";
	cout << endl;
}

#include "list.h"

int main()
{
	//list_test1();
	//list_test2();

	//wjf::test_list1();
	//wjf::test_list2();
	//wjf::test_list3();
	//wjf::test_list4();
	//wjf::test_list5();
	wjf::test_list6();

	return 0;
}
