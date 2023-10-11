#pragma once
#include "HashTable.h"
namespace wjf {
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map {
		struct MapKeyOfT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename HashBucket::HashTable<K, pair<K, V>, Hash, MapKeyOfT>::iterator iterator; //取内嵌类型要用typename
		
		iterator begin() {
			return _ht.begin();
		}

		iterator end() {
			return _ht.end();
		}
		
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _ht.Insert(kv);
		}

		V& operator[](const K& key) {
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		HashBucket::HashTable<K, pair<K, V>, Hash, MapKeyOfT> _ht; //由第二个模板参数决定存的是什么
	};

	void test_map() {
		unordered_map<string, string> dict;
		dict.insert(make_pair("sort", "排序"));
		dict.insert(make_pair("stirng", "字符串"));
		dict.insert(make_pair("left", "左边"));

		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end()) {
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;
	}
}
