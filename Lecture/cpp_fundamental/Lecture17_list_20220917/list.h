#pragma once
#include <assert.h>
#include "reverse_iterator.h"

namespace wjf
{
	template<class T>
	struct list_node // 用struct和STL库保持一致
	{
		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
	};

	//// const 迭代器复用
	// typedef _list_iterator<T, T&, T*> iterator;
	// typedef _list_iterator<T, const T&, const T*> const_iterator;
	
	template<class T, class Ref, class Ptr>
	struct _list_iterator // 设计成struct是为了可以让list中使用
	{
		typedef list_node<T> Node; 
		// typedef是受到当前访问限定符的限制的，且只在当前类域内可以使用
		typedef _list_iterator<T, Ref, Ptr> iterator;

		// typedef _list_iterator<T, T&, T*> iterator;

		//typedef bidirectional_iterator_tag iterator_category;
		//typedef T value_type;
		//typedef Ptr pointer;
		//typedef Ref reference;
		//typedef ptrdiff_t difference_type;


		Node* _node; // 迭代器结构体的唯一成员变量

		_list_iterator(Node* node)
			:_node(node)
		{}

		// 不需要析构函数，默认的析构函数不会处理Node* 指针
		// 这是合理的，因为不可能在用户使用迭代器操作后，把list中的节点给销毁了

		// 也不需要写拷贝构造，因为拷贝得到的迭代器必然要指向同一个地址，因此默认的浅拷贝就够了

		bool operator!=(const iterator& it) const
		// !=操作符，后面的const是设置const iterator * const this，不能改变传入的引用
		// 前面的const是为了权限缩小，兼容普通iterator和const_iterator
		{
			return _node != it._node;
		}

		bool operator==(const iterator& it) const
		{
			return _node == it._node;
		}

		// const_iterator和iterator的区别是是否能够修改数据，即是返回T& 还是 const T&
		// 不能使用函数重载，因为仅仅只有返回值不同的话是不构成函数重载的
		// 因此考虑使用类模板复用的方式

		//T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		//T* operator->()
		Ptr operator->()
		{ // it->->_a1 语法为了可读性，编译器进行了特殊处理，省略了一个->
			return &(operator*());
		}

		// ++等操作的返回值为iterator的原因是因为也要支持const_iterator等其他迭代器
		// 即要支持typedef _list_iterator<T, Ref, Ptr> iterator 模板实例化后得到的所有迭代器
		iterator& operator++() // 前置++
		{
			_node = _node->_next;
			return *this;
		}

		iterator operator++(int) // 后置++
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node; // Node私有
	public: // 公有，类域中都要使用
		typedef _list_iterator<T, T&, T*> iterator; 
		typedef _list_iterator<T, const T&, const T*> const_iterator;
		typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		// const_iterator begin() const 和 iterator begin() 是构成函数重载的
		// 这是因为传入的参数不同，一个是const this，一个是this
		// 因此当我们若想要使用const_iterator也要注意要传入const数据类型
		// 否则会自动使用iterator 而不是 const_iterator
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}

		iterator begin() // 闭区间
		{
			return iterator(_head->_next);
		}
		iterator end() // 开区间
		{
			return iterator(_head);
		}

		const_reverse_iterator rbegin() const // 闭区间
		{
			return const_reverse_iterator(end());
		}
		const_reverse_iterator rend() const // 开区间
		{
			return const_reverse_iterator(begin());
		}

		reverse_iterator rbegin() // 闭区间
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend() // 开区间
		{
			return reverse_iterator(begin());
		}

		// 创建并初始化哨兵位的头结点，给构造和拷贝构造复用
		void empty_initialize()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_initialize();
		}

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		
		// 现代写法
		void swap(list<T>& x)
		// void swap(list& x) // 在类域里面是可以用类名代替类型的，即省略了模板参数
		{
			std::swap(_head, x._head);
		}

		list(const list<T>& lt)
		{
			empty_initialize();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		// 浅拷贝析构没有报错的原因是因为都是内置类型默认析构不做处理
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void clear() // 清除有效数据
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it); // 迭代器失效问题
			}
		}
		//// 不复用insert
		//void push_back(const T& x)
		//{
		//	Node* tail = _head->_prev;
		//	Node* newnode = new Node(x);
		//	tail->_next = newnode;
		//	newnode->_prev = tail;
		//	newnode->_next = _head;
		//	_head->_prev = newnode;
		//}
		

		// 复用insert
		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		
		void pop_back()
		{
			erase(--end());
		}

		void pop_fornt()
		{
			erase(begin());
		}

		// pos前插入
		iterator insert(iterator pos, const T& x)
		{
			Node* curr = pos._node;
			Node* prev = curr->_prev;
			Node* newnode = new Node(x);

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = curr;
			curr->_prev = newnode;

			return iterator(newnode);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* curr = pos._node;
			Node* prev = curr->_prev;
			Node* next = curr->_next;

			prev->_next = next;
			next->_prev = prev;
			delete curr;
			
			return iterator(next);
		}

	private:
		Node* _head; // 哨兵位
	};

	// 测试
	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;

		it = lt.begin();
		while (it != lt.end())
		{
			*it *= 2;
			it++;
		}
		cout << endl;

		it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
	}

	struct Pos
	{
		int _a1;
		int _a2;
		Pos(int a1 = 0, int a2 = 0)
			:_a1(a1)
			, _a2(a2)
		{}
	};

	void test_list2()
	{
		list<Pos> lt;
		lt.push_back(Pos(10, 20));
		lt.push_back(Pos(10, 21));
		list<Pos>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << it->_a1 << " " << it->_a2 << endl;
			it++;
		}
		cout << endl;
	}

	void Func(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		cout << "const_lterator" << endl;
		while (it != lt.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
	}

	void test_list3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		
		Func(lt);
	}

	void test_list4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;

		lt.push_back(10);
		lt.push_back(20);
		lt.push_back(30);
		lt.push_back(40);

		it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
		
		lt.pop_back();
		lt.pop_back();

		for (auto e : lt)
			cout << e << " ";
		cout << endl;

		lt.clear();
	}

	void test_list5()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		list<int> copy = lt;
		for (auto& e : copy)
			e *= 2;
		cout << "copy: ";
		for (auto e : copy)
			cout << e << " ";
		cout << endl;
		
		cout << "lt: ";
		for (auto e : lt)
			cout << e << " ";
		cout << endl;

	}

	void Func2(list<int>& lt1, const list<int>& lt2)
	{
		list<int>::iterator it = lt1.begin();
		while (it != lt1.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;

		list<int>::reverse_iterator rit = lt1.rbegin();
		while (rit != lt1.rend())
		{
			cout << *rit << " ";
			rit++;
		}
		cout << endl;

		list<int>::const_iterator const_it = lt2.begin();
		while (const_it != lt2.end())
		{
			cout << *const_it << " ";
			const_it++;
		}
		cout << endl;

		list<int>::const_reverse_iterator const_rit = lt1.rbegin();
		while (const_rit != lt1.rend())
		{
			cout << *const_rit << " ";
			const_rit++;
		}
		cout << endl;
	}

	void test_list6()
	{
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		lt1.push_back(5);

		list<int> lt2;
		lt2.push_back(1);
		lt2.push_back(2);
		lt2.push_back(3);
		lt2.push_back(4);
		lt2.push_back(5);

		Func2(lt1, lt2);
	
	}
}
