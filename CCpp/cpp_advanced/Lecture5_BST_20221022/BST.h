#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace Key
{
	template<class K>
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key) // 因为要new 提供构造函数
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	public:
		bool Insert(const K& key)
		{
			if (_root == nullptr) // 空树
			{
				_root = new Node(key); // 要对Node提供构造函数
				return true;
			}
			Node* parent = nullptr;
			Node* curr = _root;
			while (curr)
			{
				if (curr->_key < key) // 要插入的key比当前_key大就往右边走
				{
					parent = curr;
					curr = curr->_right;
				}
				else if (curr->_key > key)
				{
					parent = curr;
					curr = curr->_left;
				}
				else // 默认的搜索树不允许键值冗余
					return false;
			}

			curr = new Node(key);
			if (parent->_key < key)
				parent->_right = curr;
			else
				parent->_left = curr;

			return true;
		}

		bool Find(const K& key)
		{
			Node* curr = _root;
			while (curr)
			{
				if (curr->_key < key) // 要插入的key比当前_key大就往右边走
					curr = curr->_right;
				else if (curr->_key > key)
					curr = curr->_left;
				else // 利用搜索树不允许键值冗余，若相等则是找到了
					return true;
			}
			return false; // 走完了还没找到
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* curr = _root;
			// 一共有三种情况，只有一个孩子或没有孩子的节点，这两种情况可以合在一起处理
			while (curr)
			{
				if (curr->_key < key)
				{
					parent = curr;
					curr = curr->_right;
				}
				else if (curr->_key > key)
				{
					parent = curr;
					curr = curr->_left;
				}
				else
				{ // 找到了，开始删除
					if (curr->_left == nullptr)
						// curr的左为空有三种情况
						// 首先要处理删除根节点的情况
						// 若不是根节点，则curr有可能是parent的左节点也有可能是curr的右结点
					{
						if (curr == _root)  // 若删除的是根节点，就直接挪动根节点
							_root = curr->_right;
						else
						{
							if (curr == parent->_left)
								parent->_left = curr->_right;
							else
								parent->_right = curr->_right;
						}
						delete curr;
						curr = nullptr;
					}
					else if (curr->_right == nullptr)// 同理右为空也有三种情况
					{
						if (curr == _root)
							_root = curr->_left;
						else
						{
							if (curr == parent->_left)
								parent->_left = curr->_left;
							else
								parent->_right = curr->_left;
						}
						delete curr;
						curr = nullptr;
					}

					// // 这种写法有语法错误的，若要进行迭代，必须显式地传入第一个参数minR
					//// 但Erase只有一个参数，迭代实现见下
					//else // 左右都不为空，替换法删除，这里统一实现为用右子树的最小节点
					//{ // 找右子树的最小节点
					//	Node* minR = curr->_right;
					//	while (minR->_left)
					//		minR = minR->_left;
					//	// 找到了，交换curr->_key和minR->_key
					//	::swap(curr->_key, minR->_key);
					//	// 以minR作为_root递归删除，因为要删除的minR也有可能有三种情况
					//	Erase(minR, minR->_key);
					//}

					else
					{
						Node* minParent = curr; // 极端情况，当curr就是_root时会有野指针，因此要给curr
						Node* minR = curr->_right;
						while (minR->_left) // 找右子树的最小节点
						{
							minParent = minR;
							minR = minR->_left;
						}
						::swap(curr->_key, minR->_key);
						// 考虑极端情况，若curr就是_root，此时minParent会出现空指针的情况，因此要令minParent=curr;
						// 并且若一步都没有走的话，minR不一定是minParent的左节点，需要进行判断
						if (minParent->_left == minR)
							minParent->_left = minR->_right;
						else
							minParent->_right = minR->_right;
						delete minR;
					}
					return true;
				}
			}
			return false;
		}

		void InOrder() // 封装，若直接定义public接口函数InOrder(Node* root)
			// 递归函数必须显式传入参数root进行递归，但外面取不到最开始的_root，所以封装一个函数
		{
			_InOrder(_root);
		}

		////////////////////////////////////////////

		bool FindR(const K& key) // 递归查找
		{
			return _FindR(_root, key);
		}

		bool InsertR(const K& key) // 递归插入
		{
			return _InsertR(_root, key);
		}

		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		~BSTree()
		{
			_Destroy(_root);
		}

		BSTree() = default; // Cpp11：强制编译器生成默认的构造

		//// 因为提供了拷贝构造，因此也需要显式提供一个构造函数
		//BSTree() // 自动调用初始化列表
		//{}

		BSTree(const BSTree<K>& t) // 拷贝构造，解决浅拷贝问题
		{ // 不能遍历insert，得到的BST会因为遍历顺序不同而发生变化
			_root = _Copy(t._root); //会报没有合适的默认构造函数可以用的错误，因为此时提供了构造
		}

		// 现代写法，只要完成了深拷贝就可以这么写
		// 传值传参，传入的t是一次拷贝，直接将t._root换走
		BSTree<K>& operator=(BSTree<K> t)
		{
			swap(_root, t._root);
			return *this;
		}

	private:
		Node* _Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			Node* copyRoot = new Node(root->_key); // 前序
			copyRoot->_left = _Copy(root->_left);
			copyRoot->_right = _Copy(root->_right);
			return copyRoot;
		}

		void _Destroy(Node*& root)
		{
			if (root == nullptr)
				return;
			_Destroy(root->_left); // 后序
			_Destroy(root->_right);
			delete root;
			root = nullptr;
		}

		bool _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
				return false;
			if (root->_key < key) // 去右子树找
				return _FindR(root->_right);
			else if (root->_key > key)
				return _FindR(root->_left);
			else
				return true;
		}

		bool _InsertR(Node*& root, const K& key)
			// 采用引用传参，最后一步时直接连接起来
		{
			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}
			if (root->_key < key)
				return _InsertR(root->_right, key);
			else if (root->_key > key)
				return _InsertR(root->_left, key);
			else
				return false;
		}

		bool _EraseR(Node*& root, const K& key)
		{
			if (root == nullptr)
				return false;
			if (root->_key < key)
				return _EraseR(root->_right, key);
			else if (root->_key > key)
				return _EraseR(root->_left, key);
			else
			{ // 找到了，开始删除
				Node* del = root;
				if (root->_left == nullptr)
					root = root->_right; // 因为传了引用，所以直接删除
				else if (root->_right == nullptr)
					root = root->_left;
				else
				{
					// 找右树的最左节点替换删除
					Node* minR = root->_right;
					while (minR->_left)
						minR = minR->_left;
					::swap(root->_key, minR->_key);
					return _EraseR(root->_right, key); // 缩小搜索范围后进行递归
				}
				delete del;
				return true;
			}
		}

		void _InOrder(Node* root) // 中序遍历
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}

		Node* _root = nullptr;
	};


	void TestBST1()
	{
		BSTree<int> t;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		for (auto e : a)
		{
			t.InsertR(e);
		}
		// 排序 + 去重，若可以插入进去一定是没有重复的
		t.InOrder();
		cout << endl;
		t.Erase(8);
		t.Erase(3);
		t.Erase(1);
		t.Erase(10);
		t.Erase(6);
		t.Erase(4);
		t.Erase(7);
		t.InOrder();
		cout << endl;
		t.Erase(14);
		t.InOrder();
		cout << endl;
		t.Erase(13);
		t.InOrder();
	}

	void TestBST2()
	{
		BSTree<int> t;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		for (auto e : a)
		{
			t.InsertR(e);
		}
		t.EraseR(14);
	}

	void TestBST3()
	{
		BSTree<int> t;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		for (auto e : a)
		{
			t.InsertR(e);
		}

		t.InOrder();
		cout << endl;

		BSTree<int> copy = t;
		copy.InOrder();

		cout << endl;

		BSTree<int> t1;
		t1 = t;
		t1.InOrder();
	}
}

namespace KeyValue
{
	template<class K, class V>
	struct BSTreeNode
	{
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key, const V& value) // 因为要new 提供构造函数
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	template<class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;
	public:
		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr) // 空树
			{
				_root = new Node(key, value); // 要对Node提供构造函数
				return true;
			}
			Node* parent = nullptr;
			Node* curr = _root;
			while (curr)
			{
				if (curr->_key < key) // 要插入的key比当前_key大就往右边走
				{
					parent = curr;
					curr = curr->_right;
				}
				else if (curr->_key > key)
				{
					parent = curr;
					curr = curr->_left;
				}
				else // 默认的搜索树不允许键值冗余
					return false;
			}

			curr = new Node(key, value);
			if (parent->_key < key)
				parent->_right = curr;
			else
				parent->_left = curr;

			return true;
		}

		Node* Find(const K& key)
		{
			Node* curr = _root;
			while (curr)
			{
				if (curr->_key < key) // 要插入的key比当前_key大就往右边走
					curr = curr->_right;
				else if (curr->_key > key)
					curr = curr->_left;
				else // 利用搜索树不允许键值冗余，若相等则是找到了
					return curr;
			}
			return nullptr; // 走完了还没找到
		}

		bool Erase(const K& key)
		{
			// ...
			return true;
		}

		void InOrder() // 封装，若直接定义public接口函数InOrder(Node* root)
			// 递归函数必须显式传入参数root进行递归，但外面取不到最开始的_root，所以封装一个函数
		{
			_InOrder(_root);
		}

	private:

		void _InOrder(Node* root) // 中序遍历
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_key << "：" << root->_value << endl;
			_InOrder(root->_right);
		}

		Node* _root = nullptr;
	};

	void TestBSTree1()
	{
		BSTree<string, string> dict;
		dict.Insert("sort", "排序");
		dict.Insert("left", "左边");
		dict.Insert("right", "右边");
		dict.Insert("string", "字符串");
		dict.Insert("insert", "插入");

		string str;
		while (cin >> str)
		{
			BSTreeNode<string, string>* ret = dict.Find(str);
			if (ret)
				cout << "：" << ret->_value << endl;
			else
				cout << "->" << "无此单词" << endl;
		}
	}

	void TestBSTree2()
	{
		string arr[] = { "香蕉", "苹果", "香蕉", "草莓", "香蕉", "苹果", "苹果", "苹果" };

		BSTree<string, int> countTree;
		for (auto& str : arr)
		{
			//BSTreeNode<string, int>* ret = countTree.Find(str);
			auto ret = countTree.Find(str);
			if (ret)
				ret->_value++;
			else
				countTree.Insert(str, 1);
		}

		countTree.InOrder();
	}
}
