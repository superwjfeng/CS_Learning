#pragma once
#include "RBTree.h"

namespace wjf
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const const K& key)
		{
			return _t.Insert(key);
		}

	private:
		RBTree<K, K, SetKeyOfT> _t;
	};

	void test_set1()
	{
		set<int> s;
		s.insert(3);
		s.insert(2);
		s.insert(1);
		s.insert(5);
		s.insert(3);
		s.insert(6);
		s.insert(4);
		s.insert(9);
		s.insert(7);

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << endl;
			++it;
		}
	}

}
