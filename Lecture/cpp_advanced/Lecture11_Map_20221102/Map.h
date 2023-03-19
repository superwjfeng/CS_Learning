#pragma once
#include "RBTree.h"

namespace wjf
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;
		// 对于类的内嵌类型做typedef要用typename指定，因为编译器分不清楚它是一个类型还是一个静态变量
		//typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator it;
		
		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};

	void test_map1()
	{
		map<int, int> m;
		m.insert(make_pair(1, 2));
		m.insert(make_pair(5, 2));
		m.insert(make_pair(2, 2));
	}

	void test_map2()
	{
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		map<string, int> countMap;
		for (auto& str : arr)
		{
			// 1、str不在countMap中，插入pair(str, int()),然后在对返回次数++
			// 2、str在countMap中，返回value(次数)的引用，次数++;
			countMap[str]++;
		}

		map<string, int>::iterator it = countMap.begin();
		while (it != countMap.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
		for (auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
}
