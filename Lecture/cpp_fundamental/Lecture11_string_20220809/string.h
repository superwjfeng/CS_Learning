#pragma once
#include <string.h>

namespace wjf
{
	class string
	{
	public:
		typedef char* iterator; // 在string中的迭代器就是对原生指针的封装
		typedef const char* const_iterator;
		// 左闭右开
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		//string()
		//	:_str(new char[1])
		//	, _size(0)
		//	, _capacity(0)
		//{
		//	_str[0] = '\0';
		//}

		//// 不能这么初始化空对象
		//string()
		//	:_str(nullptr)
		//	, _size(0)
		//	, _capacity(0)
		//{
		//	_str[0] = '\0';
		//}
		//string(const char* str = "\0")

		//string(const char* str = "")
		//	//	:_str(str) // 不能将字符串常量给char* _str
		//	:_str(new char[strlen(str) + 1])
		//	, _size(strlen(str))
		//	, _capacity(strlen(str))
		//	
		//	// // 这样初始化是错误的，因为初始化是根据类成员声明的顺序来初始化
		//	// // 因此首先初始化_str，此时_capacity还是随机值
		//	//:_size(strlen(str))
		//	//, _capacity(_size)
		//	//, _str(new char[_capacity + 1])
		//{
		//	strcpy(_str, str);
		//}

		// 推荐不使用初始化列表进行初始化，因为会产生初始化顺序依赖问题
		// 而且因为都是内置类型，所以不影响
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//// 传统写法
		//string(const string& s)
		//	:_str(new char[s._capacity + 1])
		//	, _size(s._size)
		//	, _capacity(s._capacity)
		//{
		//	strcpy(_str, s._str);
		//}

		//string& operator=(const string& s)
		//{
		//	if (this != &s) // 防止自己给自己赋值
		//	{
		//		char* tmp = new char[s._capacity + 1];
		//		strcpy(tmp, s._str);
		//		delete[] _str;
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}

		// 现代写法：安排一个打工人
		void swap(string& tmp)
		{
			::swap(_str, tmp._str);
			::swap(_size, tmp._size);
			::swap(_capacity, tmp._capacity);
		}

		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0) // 不给初始值的话，delete随机值会崩溃
		{
			string tmp(s._str);
			swap(tmp); // this->swap(tmp);
		}

		//string& operator=(const string& s)
		//{
		//	if (this != &s) // 防止自己给自己赋值
		//	{
		//		string tmp(s);
		//		::swap(*this, tmp);
		//	}
		//	return *this;
		//}

		// s顶替tmp做打工人
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		const char* c_str() const
		{
			return _str;
		}

		size_t size() const // 普通对象和const对象都可以使用
		{
			return _size;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		// 1、避免最初的扩容开销 2、用来复用
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;

				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			// 满了就扩容
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = ch;
			_str[++_size] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			// 满了就扩容
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			// strcat(_str, str); // 不要用strcat，因为要找\0，是一个失败的设计
			_size += len;
		}

		// 重载
		void append(const string& s)
		{
			append(s._str);
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size); // =的时候就是尾插
			// 满了就扩容
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			// 挪数据
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			// 插入字符
			_str[pos] = ch;
			++_size;

			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			// 满了就扩容
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			// 挪数据
			size_t end = _size + len;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				--end;
			}
			// 插入字符串
			strncpy(_str + pos, str, len);
			_size += len;
			return *this;
		}

		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos + len >= _size) // 删到底
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else // 正常删，要挪数据
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}

		//size_t find(char ch, size_t pos = 0)
		//{
		//	assert(pos < _size);
		//	size_t i = pos;
		//	while (_str[i] != ch && i++ < _size);
		//	if (i == _size + 1)
		//		return npos;
		//	else
		//		return i;
		//}

		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++)
			{
				if (ch == _str[i])
					return i;
			}
			return npos;
		}

		size_t find(const char* sub, size_t pos = 0) const
		{
			assert(sub);
			size_t lenSub = strlen(sub);
			assert(pos + lenSub < _size);
			// KMP BM 算法
			const char* ptr = strstr(_str + pos, sub);
			if (!ptr)
				return npos;
			else
				return ptr - _str;
		}

		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}
		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator>=(const string& s) const
		{
			return *this > s || *this == s;
		}
		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}
		bool operator<(const string& s) const
		{
			return !(*this >= s);
		}
		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}

		string substr(size_t pos, size_t len = npos) const
		{
			assert(pos < _size);
			size_t realLen = len;
			if (len == npos || pos + len > _size)
				realLen = _size - pos;
			string sub;
			for (size_t i = 0; i < realLen; i++)
			{
				sub += _str[pos + i];
			}
			return sub;
		}

		void resize(size_t n, char ch = '\0')
		{// 若需要resize到的尺寸大于_size，就插入数据，否则就删除数据
			if (n > _size)
			{// 插入数据
				reserve(n);
				for (size_t i = _size; i < n - _size; i++)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{// 删除数据
				_str[n] = '\0';
				_size = n;
			}
		}

	private:
		// VS的STL中的string类对string小对象做了优化，因此实际的实现也要做大幅度改变
		// Linux中的实现又是不同的
		// < 16 字符串存在buff数组中
		// >= 16 存在_str指向的堆空间中
		// 优点是提高了小的string对象效率，缺点是令每一个string类初始空间变大了，为28字节
		// char _buff[16];
		char* _str;
		size_t _size;
		size_t _capacity;
		// cosnt static Cpp的特殊处理，是一个bug
	public:
		const static size_t npos = -1;
	};

	// size_t string::npos = -1;

	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			out << s[i];
		}
		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		char ch;
		// in >> ch;
		ch = in.get();
		while (ch != ' ' || ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}

	void test_string1()
	{
		string s1("hello world");
		string s2;

		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;

		for (size_t i = 0; i < s1.size(); i++)
		{
			cout << s1[i] << " ";
		}
		cout << endl;
 
		for (size_t i = 0; i < s1.size(); i++)
		{
			cout << ++s1[i] << " ";
		}
		cout << endl;
	}

	void test_string2()
	{
		string s1("hello world");
		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			cout << *it++ << " ";
		}
		cout << endl;

		for (auto ch : s1)
		{
			// 范围for的本质就是替换成迭代器，ch替换成it;
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string3()
	{
		string s1("hello world");
		string s2(s1);
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		s2[0] = 'x';

		string s3("11111111111111111111");
		s1 = s3; // 用默认的operator=存在两大问题
		// 1、浅拷贝问题
		// 2、原s1仍然存在，由于指针指向s3造成了s1内存泄漏
		cout << s1.c_str() << endl;
	}

	void test_string4()
	{
		string s1("hello world");
		string s2("xxxxxxxxxxx");
		s1.swap(s2);
		swap(s1, s2);
	}

	void test_string5()
	{
		string s1("hello world");
		cout << s1.c_str() << endl;
		s1.push_back('x');
		cout << s1.c_str() << endl;
		s1 += 'y';
		s1 += 'z';
		s1 += 'z';
		s1 += 'z';
		s1 += 'z';
		cout << s1.c_str() << endl;
	}

	void test_string6()
	{
		string s1("hello");
		cout << s1.c_str() << endl;
		s1 += ' ';
		s1.append("world");
		s1 += " welcome";
		cout << s1.c_str() << endl;

		s1.insert(5, '#');
		cout << s1.c_str() << endl;
	}

	void test_string7()
	{	
		string s1("hello");
		s1.erase(2);
		cout << s1.c_str() << endl;
		string s2("hello");
		s2.erase(2, 2);
		cout << s2.c_str() << endl;
	}

	void test_string8()
	{
		string s1("hello");
		cout << s1 << endl;
		cout << s1.c_str() << endl;
		s1 += '\0';
		s1 += "world";
		cout << s1 << endl;
		cout << s1.c_str() << endl;
	}

	void test_string9()
	{
		string s1("hello");
		cout << s1 << endl;
		cout << s1.find('z') << endl;
		string s2("helloworld");
		cout << s2 << endl;
		cout << s2.find("low") << endl;
	}

	void test_string10()
	{
		string s1("helloworld");
		string s2 = s1.substr(3, 4);
		cout << s2 << endl;
	}

	void test_string11()
	{
		std::string s1;
		s1.resize(20);

		std::string s2("helloworld22");
		s2.resize(20, 'x');
		
		s2.resize(10);
	}

	void test_string12()
	{
		string s0;
		string s1("111111");
		string s2("1111111111111111111111111111111111111111111");
		cout << sizeof(s0) << endl;
		cout << sizeof(s1) << endl;
		cout << sizeof(s2) << endl;
	}
}


