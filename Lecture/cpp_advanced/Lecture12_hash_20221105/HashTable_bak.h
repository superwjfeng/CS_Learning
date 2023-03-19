#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class K>
struct HashFunc {// 仿函数类
	size_t operator()(const K& key) {
		return (size_t)key;
	}
};

template<> // STL库中的unordered_map对string类进行了特化处理
struct HashFunc<string> {// 专门处理string转换的仿函数类
	size_t operator()(const string& key) {
		size_t val = 0;
		for (auto ch : key) { // BKDR字符串哈希算法
			val *= 131;
			val += ch;
		}
		return val;
	}
};

namespace CloseHash {
	enum State {
		EMPTY,
		EXIST,
		DELETE
	};

	template<class K, class V>
	struct HashData {
		pair<K, V> _kv;
		State _state = EMPTY; // 缺省值为空
	};



	//struct HashFuncString // 专门处理string转换的仿函数类
	//{
	//	size_t operator()(const string& key)
	//	{
	//		size_t val = 0;
	//		for (auto ch : key)
	//			val += ch;
	//		return val;
	//	}
	//};

	template<class K, class V, class Hash = HashFunc<K>> // Hash仿函数将Key转化为可以进行运算的类型
	class HashTable {
	public:
		bool Insert(const pair<K, V>& kv) {
			if (Find(kv.first)) // 已经有了就不插入
				return false;
			//if (_tables.size() == 0 || 10 * _size / _tables.size >= 7) // 扩容
			//{
			//	size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			//	vector<HashData<K, V>> newTables;
			//	newTables.resize(newSize);
			//	// 旧表的数据映射到新表
			//	for ()
			//	{
			//		// 重新建立映射关系非常麻烦，原来冲突的可能不冲突了，原来不冲突的可能冲突了...
			//	}
			//	_tables.swap(newTables);
			//}
			if (_tables.size() == 0 || 10 * _size / _tables.size() > 7) {// 计算负载因子 到了扩容
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				HashTable<K, V, Hash> newHT;
				newHT._tables.resize(newSize);
				// 旧表的数据映射到新表
				for (auto e : _tables) {
					if (e._state == EXIST)
						newHT.Insert(e._kv); // 直接对新表调用Insert
					// 第一次是0，会进到if里，会直接给一张size为10的新的哈希表，然后插入第一个值
				}
				_tables.swap(newHT._tables); // 交换 *this 和newHT._tables地址，newHT在Insert结束后会被析构
			}

			// 线性探测
			Hash hash; // 实例化仿函数对象
			size_t hashi = hash(kv.first) % _tables.size(); // 不能用capacity，因为capacity比size多的空间不能用
			// 所以尽量保持size和capacity相等，开空间用resize
			// 负数即有符号整形和无符号整形运算时会被整型提升成无符号整形，也适用于哈希表

			while (_tables[hashi]._state == EXIST) {
				hashi++;
				hashi %= _tables.size();
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			_size++;

			return true;

			//// 二次探测
			//Hash hash; // 实例化仿函数对象
			//size_t start = hash(kv.first) % _tables.size(); // 不能用capacity，因为capacity比size多的空间不能用
			//size_t i = 0;
			//size_t hashi = start;
			//while (_tables[hashi]._state == EXIST) {
			//	//hashi++;
			//	hashi = start + i * i;
			//	hashi %= _tables.size();
			//}
			//_tables[hashi]._kv = kv;
			//_tables[hashi]._state = EXIST;
			//_size++;

			//return true;

		}

		HashData<K, V>* Find(const K& key) {
			if (_tables.size() == 0)
				return nullptr;

			// 有这样一种可能性，连续不断的交替插入和删除，可能会出现所有位置都是DELETE，但这种可能性很小
			Hash hash; // 实例化仿函数对象
			size_t start = hash(key) % _tables.size();
			size_t hashi = start;
			while (_tables[hashi]._state != EMPTY) {// DELELTE也要查
				if (_tables[hashi]._state != DELETE && _tables[hashi]._kv.first == key)
					return &_tables[hashi];
				hashi++;
				hashi %= _tables.size(); //有可能出界

				if (hashi == start)
					break;
			}
			return nullptr;
		}

		bool Erase(const K& key) {
			HashData<K, V>* ret = Find(key);
			if (ret) {// 找到了
				ret->_state = DELETE;
				_size--;
				return true;
			}
			else // 没找到
				return false;
		}

		void Print() {
			for (size_t i = 0; i < _tables.size(); i++) {
				if (_tables[i]._state == EXIST)
					printf("[%d:%d] ", i, _tables[i]._kv.first);
				else
					printf("[%d:**] ", i);
			}
			cout << endl;
		}

	private:
		vector<HashData<K, V>> _tables;
		size_t _size = 0; // 存储有多少个有效数据
	};

	void TestHT1() {
		int a[] = { 1, 11, 4, 15, 26, 7, 44, 9 };
		HashTable<int, int> ht;
		for (auto e : a) {
			ht.Insert(make_pair(e, e));
		}

		ht.Print();
		ht.Erase(4);
		cout << ht.Find(44)->_kv.first << endl;
		cout << ht.Find(4) << endl;
		ht.Print();
	}

	void TestHT2() {
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<string, int> countHT;
		for (auto& str : arr) {
			auto ptr = countHT.Find(str);
			if (ptr)
				ptr->_kv.second++;
			else
				countHT.Insert(make_pair(str, 1));
		}
		countHT.Print();
	}
}

namespace HashBucket {
	template<class K, class V>
	struct HashNode {
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable {
		typedef HashNode<K, V> Node;
	public:
		//vector<Node*> 会调用自己的析构释放掉，但下面挂的桶不会
		~HashTable() {
			for (size_t i = 0; i < _tables.size(); i++) {
				Node* curr = _tables[i];
				while (curr) {
					Node* next = curr->_next;
					delete(curr);
					curr = next;
				}
				_tables[i] = nullptr;
			}
		}

		//C++11哈希表的扩容尺寸用的是间隔将近2倍的素数
		inline size_t __stl_next_prime(size_t n) {
			static const int __stl_num_primes = 28; //`const` 类型的int静态变量可以给缺省值
			static const size_t __stl_prime_list[__stl_num_primes] = {
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			for (size_t i = 0; i < __stl_num_primes; i++) {
				if (__stl_prime_list[i] > n) {
					return __stl_prime_list[i];
				}
			}
			return -1;
		}


		bool Insert(const pair<K, V>& kv) {
			// 去重
			if (Find(kv.first))
				return false;

			Hash hash; //仿函数实例化
			// 负载因子到1就扩容
			if (_size == _tables.size()) {
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				vector<Node*> newTables;
				//newTables.resize(newSize, nullptr);
				newTables.resize(__stl_next_prime(_tables.size()), nullptr);
				// 把旧表中的节点拆下来依次挂到新表上
				for (size_t i = 0; i < _tables.size(); i++) {
					Node* curr = _tables[i];
					while (curr) {
						Node* next = curr->_next; // 保存原表中的next，方便下回继续拆
						size_t hashi = hash(curr->_kv.first) % newTables.size(); // 算新表中的位置
						curr->_next = newTables[hashi]; // 在新表中头插
						newTables[hashi] = curr;
						curr = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}

			
			size_t hashi = hash(kv.first) % _tables.size();
			// 考虑用头插
			Node* newnode = new Node(kv); // new出来的是在堆上的实例化类对象，出Insert不会被析构
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			_size++;
			return true;
		}

		Node* Find(const K& key) {
			if (_tables.size() == 0) // 防止除零错误
				return nullptr;
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* curr = _tables[hashi];
			while (curr) {
				if (curr->_kv.first == key)
					return curr;	
				curr = curr->_next;
			}
			return nullptr;
		}

		bool Erase(const K& key) {
			if (_tables.size() == 0) { // 防止除零错误
				return false; 
			}

			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* curr = _tables[hashi];
			
			while (curr) {
				if (curr->_kv.first == key) {
					//1. 头删
					if (prev == nullptr) {
						_tables[hashi] = curr->_next;
					}
					else { //2. 中间删
						prev->_next = curr->_next;
					}
					delete curr;
					_size--;
					return true;
				}
				// 找目标
				prev = curr;
				curr = curr->_next;
			}
			return false;
		}

		size_t Size() {
			return _size;
		}

		// 表的长度
		size_t TableSize() {
			return _tables.size();
		}

		// 桶的个数
		size_t BucketNum() {
			size_t num = 0;
			for (size_t i = 0; i < _tables.size(); i++) {
				if (_tables[i]) { //存的是指针
					num++;
				}
			}
		}
	private:
		vector<Node*> _tables;
		size_t _size = 0; // 存储有效数据个数
	};

	void TestHT1() {
		int a[] = { 1, 11, 4, 15, 26, 7, 44, 55, 99, 78};
		HashTable<int, int> ht;
		for (auto e : a) {
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(22, 22));
	}

	void TestHT2() {
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<string, int> countHT;
		for (auto& str : arr) {
			auto ptr = countHT.Find(str);
			if (ptr)
				ptr->_kv.second++;
			else
				countHT.Insert(make_pair(str, 1));
		}
	}
}
