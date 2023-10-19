#pragma once
#include <assert.h>
#include "../Lecture17_list_20220917/reverse_iterator.h"

namespace wjf
{
  template<class T>
  class vector
  {
  public:
    typedef T* iterator;
    typedef const T* const_iterator;
    
    // 复用list中的reverse_iterator
    typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
    typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;


    iterator begin()
    {
      return _start;
    }

    iterator end()
    {
      return _finish;
    }

    const iterator begin() const
    {
      return _start;
    }

    const iterator end() const
    {
      return _finish;
    }

    reverse_iterator rbegin()
    {
      return reverse_iterator(end());
    }

    reverse_iterator rend()
    {
      return reverse_iterator(begin());
    }

    const reverse_iterator rbegin() const
    {
      return reverse_iterator(end());
    }

    const reverse_iterator rend() const
    {
      return reverse_iterator(begin());
    }

    vector()
      :_start(nullptr)
      , _finish(nullptr)
      , _end_of_storage(nullptr)
    {}
    
    //// 传统写法1 
    //vector(const vector<T>& v) // v2(v1)
    //{
    //	_start = new T[v.size()]; // 开v.capacity()个空间也可以，各有各的优势和劣势
    //	// 不能使用memcpy，memcpy也是浅拷贝，当出现类似与vector<vector<int>> 这种多维数组就会有问题
    //	//	memcpy(_start, v._start, sizeof(T) * v.size());
    //	for (size_t i = 0; i < v.size(); i++)
    //		_start[i] = v._start[i];
    //	_finish = _start + v.size();
    //	_end_of_storage = _start + v.size();
    //}

    //// 传统写法2
    //vector(const vector<T>& v)
    //	:_start(nullptr)
    //	, _finish(nullptr)
    //	, _end_of_storage(nullptr)
    //{
    //	reserve(v.size());
    //	for (const auto& e : v) // 若是vector则传值要深拷贝，因此用引用
    //	{
    //		push_back(e); // push_back 会自动处理_finish和_end_of_storage
    //	}
    //}

    // 现代写法
    // 提供一个迭代器区间构造
    template <class InputIterator>
    vector(InputIterator first, InputIterator last)
      :_start(nullptr)
      , _finish(nullptr)
      , _end_of_storage(nullptr)
    {
      while (first != last)
      {
        push_back(*first);
        first++;
      }
    }

    void swap(vector<T>& v)
    {
      std::swap(_start, v._start);
      std::swap(_finish, v._finish);
      std::swap(_end_of_storage, v._end_of_storage);
    }

    vector<T> operator=(vector<T> v)
    {
      swap(v);
      return *this;
    }
    
    vector(const vector<T>& v)
      :_start(nullptr)
      , _finish(nullptr)
      , _end_of_storage(nullptr)
    {
      vector<T> tmp(v.begin(), v.end());
      swap(tmp);
    }

    vector(size_t n, const T& val = T())
      :_start(nullptr)
      , _finish(nullptr)
      , _end_of_storage(nullptr)
    {
      reserve(n);
      for (size_t i = 0; i < n; i++)
        push_back(val); // 插入n个val来完成构造
    }

    //支持初始化列表的构造函数
    vector(initializer_list<T> il)
      :_start(nullptr)
      , _finish(nullptr)
      , _end_of_storage(nullptr)
    {
      reserve(il.size());
      for (auto& e : il) {
        push_back(e);
      }
    }

    ~vector()
    {
      delete[] _start;
      _start = _finish = _end_of_storage = nullptr;
    }

    size_t capacity() const
    {
      return _end_of_storage - _start;
    }

    size_t size() const
    {
      return _finish - _start;
    }

    T& operator[](size_t pos)
    {
      assert(pos < size());
      return _start[pos];
    }

    const T& operator[](size_t pos) const
    {
      assert(pos < size());
      return _start[pos];
    }

    // 一个关于reserve的错误，reserve之后直接用[]进行访问
    // 这是因为reserve之后只会改变capacity，而不会改变size
    // 也就是不会初始化，访问随机值出错。resize才会进行初始化
    void reserve(size_t n)
    {
      if (n > capacity())
      {
        size_t sz = size();
        T* tmp = new T[n];
        if (_start)
        {
          //memcpy(tmp, _start, sizeof(T) * sz);
          for (size_t i = 0; i < sz; i++)
            tmp[i] = _start[i];
          delete[] _start;
        }
        _start = tmp;
        //_finish = _start + size();
        //// 这样写会报错，_start地址已经是tmp了，但接下来的赋值调用size()
        //// 会变成 _finish = _start + (_finish - _start) = _finish == nullptr
        //// 会造成对空指针解引用的错误，因此改用在开头保存sz的方案
        _finish = _start + sz;
        _end_of_storage = _start + n;
      }
    }

    void resize(size_t n, const T& val = T()) // T() 是默认全缺省拷贝构造
    {
      if (n > capacity())
      {
        reserve(n);
      }
      if (n > size()) // 这种情况将 n>capacity() 也包括了
      { // 初始化填值
        while (_finish < _start + n)
        {
          *_finish = val;
          _finish++;
        }
      }
      else // 删除数据
        _finish = _start + n;
    }

    T& front()
    {
      assert(size() > 0);
      return *_start;
    }

    T& back()
    {
      assert(size() > 0);
      return *(_finish - 1);
    }

    void push_back(const T& x)
    {
      if (_finish == _end_of_storage)
      {
        reserve(capacity() == 0 ? 4 : capacity() * 2);
      }
      *_finish = x;
      _finish++;

    }

    void pop_back()
    {
      assert(_finish > _start);
      _finish--;
    }

    iterator insert(iterator pos, const T& x)
    {
      assert(pos >= _start && pos <= _finish);
      if (_finish == _end_of_storage) // 扩容
      {// 解决迭代器失效问题：计算pos和_start的相对位置，扩容后令原pos重新指向
        size_t len = pos - _start;
        reserve(capacity() == 0 ? 4 : capacity() * 2);
        pos = _start + len;
      }
      iterator end = _finish - 1;
      while (end >= pos) // 挪动数据
      {
        *(end + 1) = *end;
        end--;
      }
      *pos = x;
      _finish++;
      return pos;
    }
    //void erase(iterator pos)
    //{
    //	assert(pos >= _start && pos < _finish);
    //	// 从前往后挪动数据
    //	iterator begin = pos + 1;
    //	while (begin < _finish)
    //	{
    //		*(begin - 1) = *begin;
    //		begin++;
    //	}
    //	_finish--;
    //}
    // STL规定了erase要返回删除位置的下一个位置迭代器
    iterator erase(iterator pos)
    {
      assert(pos >= _start && pos < _finish);
      // 从前往后挪动数据
      iterator begin = pos + 1;
      while (begin < _finish)
      {
        *(begin - 1) = *begin;
        begin++;
      }
      _finish--;
      return pos; // 返回删除数据的下一个位置 还是pos
    }
  private:
    iterator _start;
    iterator _finish;
    iterator _end_of_storage;
  };

  // class外的测试
  void test_vector1() // 测试构造函数
  {
    // i是d的临时变量的引用，临时变量具有常性，引用为int则进行了权限放大
    double d = 2.2;
    //int& i = d;
    const int& i = d;

    vector<string> v;
    v.push_back("xxxxxxx");
  }

  void test_vector2() // 测试push_back和迭代器
  {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    for (size_t i = 0; i < v.size(); i++)
    {
      cout << v[i] << " ";
    }
    cout << endl;
    
    vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
      cout << *it << " ";
      it++;
    }
    cout << endl;

    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;

    v.pop_back();
    v.pop_back();

    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;
  }

  void test_vector3() // 测试insert、erase和迭代器失效
  {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    //v.push_back(5);

    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;
    
    auto p = find(v.begin(), v.end(), 3);
    if (p != v.end())
    {
      // 在p位置修改插入数据以后不要访问p，因为p可能失效
      v.insert(p, 30);
      //cout << *p << endl;
      //v.insert(p, 30);
    }

    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;

    auto pErase = find(v.begin(), v.end(), 30);
    if (pErase != v.end())
    {
      v.erase(pErase);
      v.erase(v.begin());
      v.erase(v.end() - 1);
    }
    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;
  }

  void test_vector4()
  {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
  //	v.push_back(4);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    auto it = v.begin();
    while (it != v.end())
    {
      if (*it % 2 == 0)
        //v.erase(it);
        it = v.erase(it);
      else
        it++; // erase之后更新迭代器
    }
    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;
  }

  void test_vector5()
  {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(4);

    vector<int> v1(v);
    v[0] *= 2;
    for (auto e : v1)
      cout << e << " ";
    cout << endl;
  }

  void test_vector6()
  {
    string s("hello world");
    vector<int> v(s.begin(), s.end());
    for (auto e : v)
      cout << e << " ";
    cout << endl;
  }

  //void test_vector7()
  //{
  //	int i = 0;
  //	int j = int(); // 为了适应模板，内置数据类型也要有默认构造函数
  //	int k = int(10);

  //	vector<int> v1(10);
  //	for (auto e : v1)
  //		cout << e << " ";
  //	cout << endl;

  //	//vector<int> v2(10, 1); 
  //	//// 两个int将会匹配vector(InputIterator first, InputIterator last)
  //	//// 对int解引用报错
  //	//for (auto e : v2)
  //	//	cout << e << " ";
  //	//cout << endl;

  //	vector<char> v3(10, 'a');
  //	for (auto e : v3)
  //		cout << e << " ";
  //	cout << endl;
  //}

  void test_vector8() // 测试resize
  {
    vector<int> v1;
    v1.resize(10, 0);
    for (auto e : v1)
      cout << e << " ";
    cout << endl;

    vector<int> v2;
    v2.reserve(16);
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(4);
    v2.resize(6);
    for (auto e : v2)
      cout << e << " ";
    cout << endl;
  }

  class Solution {
  public:
  //	vector<vector<int>> generate(int numRows)
    void generate(int numRows)
    {
      vector<vector<int>> vv;
      //vector<vector<int>> test = vv;
      vv.resize(numRows); // resize初始化每一行
      // 每一行的首尾元素赋为1
      for (size_t i = 0; i < vv.size(); i++)
      {
        vv[i].resize(i + 1, 0);
        vv[i].front() = vv[i].back() = 1;
      }
      for (size_t i = 0; i < vv.size(); i++)
      {
        for (size_t j = 0; j < vv[i].size(); j++)
          if (!vv[i][j])
            vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
      }
      //return vv;
      vector<vector<int>> ret = vv;
      vector<vector<int>> ret2 = vv;
    }
  };

  void test_vector9()
  {
    Solution().generate(5);
  }

  //void test_vector10() // 测试对reverse_iterator的复用
  //{
  //	vector<int> v;
  //	v.push_back(1);
  //	v.push_back(2);
  //	v.push_back(3);
  //	v.push_back(4);
  //	v.push_back(5);

  //	vector<int>::iterator it = v.begin();
  //	while (it != v.end())
  //		cout << *it++ << " ";
  //	cout << endl;

  //	vector<int>::const_iterator cit = v.begin();
  //	while (cit != v.end())
  //		cout << *cit++ << " ";
  //	cout << endl;

  //	vector<int>::reverse_iterator rit = v.rbegin();
  //	while (rit != v.rend())
  //		cout << *rit++ << " ";
  //	cout << endl;
  //	
  //	vector<int>::const_reverse_iterator crit = v.rbegin();
  //	while (crit != v.rend())
  //		cout << *crit++ << " ";
  //	cout << endl;
  //}

  void test_vector11() {
    vector<int> v{ 1,2,3,4,5,6 };
    for (auto e : v) {
      cout << e << endl;
    }
    cout << endl;
  }

  void test_vector12() {
    vector<bool> v{ true, false, true };
  }
}
