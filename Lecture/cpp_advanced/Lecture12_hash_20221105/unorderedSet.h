#pragma once
#include "HashTable.h"
namespace wjf {
	template<class K, class Hash = HashFunc<K>>
	class unordered_set {
		struct SetKeyOfT {
			const K& operator()(const K& key) {
				return key;
			}
		};
	public:
		typedef typename HashBucket::HashTable<K, K, Hash, SetKeyOfT>::iterator iterator; //取内嵌类型要用typename

		iterator begin() {
			return _ht.begin();
		}

		iterator end() {
			return _ht.end();
		}

		pair<iterator, bool> insert(const K& key) {
			return _ht.Insert(key);
		}
	private:
		HashBucket::HashTable<K, K, Hash, SetKeyOfT> _ht; //由第二个模板参数决定存的是什么
	};
	void test_set()
	{
		unordered_set<int> s;
		s.insert(2);
		s.insert(3);
		s.insert(1);
		s.insert(2);
		s.insert(5);

		unordered_set<int>::iterator it = s.begin();
		//auto it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}
