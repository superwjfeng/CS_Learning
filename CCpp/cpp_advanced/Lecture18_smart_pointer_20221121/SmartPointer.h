#pragma once
#include <memory>
#include <iostream>
using namespace std;

namespace wjf {
// 利用RAII设计delete资源的类
template <class T>
class SmartPtr {
 public:
  SmartPtr(T* ptr) : _ptr(ptr) {}

  ~SmartPtr() {
    cout << "delete: " << _ptr << endl;
    delete _ptr;
  }

  T& operator*() { return *_ptr; }

  T* operator->() { return _ptr; }

 private:
  T* _ptr;
};

void Func() {
  /*int* p1 = new int;
  int* p2 = new int;
  SmartPtr<int> sp1(p1);
  SmartPtr<int> sp2(p2);*/

  SmartPtr<int> sp1(new int);
  SmartPtr<int> sp2(new int);
}

class A {
 public:
  ~A() { cout << "~A()" << endl; }

  // private:
  int _a1 = 0;
  int _a2 = 0;
};

void test_unique_ptr() {
  std::unique_ptr<A> up1(new A);
  //	std::unique_ptr<A> up2(up1);
}

void test_shared_ptr() {
  std::shared_ptr<A> sp1(new A);
  std::shared_ptr<A> sp2(sp1);
  sp1->_a1++;
  sp2->_a1++;
  sp1->_a2++;
  sp2->_a2++;
  cout << sp1->_a1 << " " << sp2->_a2 << endl;
}

template <class T>
struct Delete {
  void operator()(T* ptr) {
    cout << "delete" << ptr << endl;
    delete ptr;
  }
};

template <class T, class D = Delete<T>>
class shared_ptr {
 public:
  shared_ptr(T* ptr = nullptr)
      : _ptr(ptr),
        _pCount(new int(1))  // 给一个计数器
  {}

  ~shared_ptr() { Release(); }

  void Release() {
    if (--(*_pCount) == 0) {  // 给对象赋值是建立在*this目标已经定义的情况下的
      // 此时计数器至少为1，若没有这步，直接更改指向对象会造成内存泄漏
      cout << "Delete: " << _ptr << endl;
      // delete _ptr;
      D()(_ptr);
      delete _pCount;
    }
  }

  shared_ptr(shared_ptr<T>& sp) : _ptr(sp._ptr), _pCount(sp._pCount) {
    (*_pCount)++;
  }

  shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
    // 防止自己给自己赋值
    if (_ptr == sp._ptr) {
      return *this;
    }

    Release();

    _ptr = sp._ptr;
    _pCount = sp._pCount;

    (*_pCount)++;
    return *this;
  }

  T& operator*() { return *_ptr; }

  T* operator->() { return _ptr; }

  T* get() {  // 给weak_ptr使用
    return _ptr;
  }

 private:
  T* _ptr;
  int* _pCount;  // 计数器
  D _del;
};

void test_shared_ptr1() {
  wjf::shared_ptr<A> sp1(new A);
  wjf::shared_ptr<A> sp2(sp1);
  wjf::shared_ptr<A> sp3(sp1);

  sp1->_a1++;
  sp1->_a2++;
  cout << sp2->_a1 << ":" << sp2->_a2 << endl;
  sp2->_a1++;
  sp2->_a2++;
  cout << sp1->_a1 << ":" << sp1->_a2 << endl;

  wjf::shared_ptr<A> sp5(new A);
  wjf::shared_ptr<A> sp6(sp5);
  sp1 = sp5;
  sp2 = sp5;
  sp3 = sp5;

  // 自己给自己赋值
  wjf::shared_ptr<int> sp4(new int);
  sp4 = sp4;
  sp1 = sp5;  // 这也属于自己给自己赋值，因为管理的是完全相同的资源
  // 虽然不会出错，但没有必要
}

struct Node {
  int _val;
  // std::shared_ptr<Node> _next;
  // std::shared_ptr<Node> _prev;
  std::weak_ptr<Node> _next;  // 解决循环引用，不会增加计数
  std::weak_ptr<Node> _prev;

  ~Node() { cout << "~Node()" << endl; }
};

// 循环引用，没有报错是因为main退出后会自动清理资源
// 但很多程序是需要长时间运行的，在这种情况下的内存泄漏是很可怕的
void test_shared_ptr2() {
  std::shared_ptr<Node> n1(new Node);
  std::shared_ptr<Node> n2(new Node);
  n1->_next = n2;
  n2->_prev = n1;
}

template <class T>
struct DeleteArray {
  void operator()(T* ptr) {
    cout << "delete" << ptr << endl;
    delete[] ptr;
  }
};

template <class T>
struct Free {
  void operator()(T* ptr) {
    cout << "free" << ptr << endl;
    free(ptr);
  }
};

template <class T>
class weak_ptr {
 public:
  weak_ptr() : _ptr(nullptr) {}

  weak_ptr(const shared_ptr<T>& sp)  // 支持对shared_ptr的拷贝构造
      : _ptr(sp.get()) {}

  weak_ptr(const weak_ptr<T>& wp) : _ptr(wp._ptr) {}

  weak_ptr<T>& operator=(const shared_ptr<T>& sp) {
    _ptr = sp.get();
    return *this;
  }

  T& operator*() { return *_ptr; }

  T* operator->() { return _ptr; }

 private:
  T* _ptr;
};

// 定制删除器
void test_shared_ptr3() {
  ////仿函数对象
  // std::shared_ptr<Node> n1(new Node[5], DeleteArray<Node>());
  // std::shared_ptr<Node> n2(new Node);
  // std::shared_ptr<int> n3(new int[5], DeleteArray<int>());
  // std::shared_ptr<int> n4((int*)malloc(sizeof(12)), Free<int>());

  // lambda
  std::shared_ptr<Node> n1(new Node[5], [](Node* ptr) { delete[] ptr; });
  std::shared_ptr<Node> n2(new Node);
  std::shared_ptr<int> n3(new int[5], [](int* ptr) { delete[] ptr; });
  std::shared_ptr<int> n4((int*)malloc(sizeof(12)),
                          [](int* ptr) { free(ptr); });
}

}  // namespace wjf
