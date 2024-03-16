#include <iostream>
#include <mutex>

// for test
class A {
 public:
  ~A() { std::cout << "~A()" << std::endl; }
  int _a1 = 0;
  int _a2 = 0;
};

template <typename T>
struct Delete {
  void operator()(T *ptr) {
    std::cout << "delete" << std::endl;
    delete ptr;
  }
};

template <typename T>
struct DeleteArray {
  void operator()(T *ptr) {
    std::cout << "delete array" << std::endl;
    delete[] ptr;
  }
};

template <typename T>
class Free {
 public:
  void operator()(T *ptr) {
    std::cout << "free" << std::endl;
    free(ptr);
  }
};

template <typename T, typename D = Delete<T>>
class SharedPtr {
 public:
  SharedPtr(T *ptr = nullptr)
      : _ptr(ptr), _pCount(new int(1)), _mutex(new std::mutex) {
    std::cout << "New Shared Pointer" << std::endl;
  }

  SharedPtr(SharedPtr<T> &sp)
      : _ptr(sp._ptr), _pCount(sp._pCount), _mutex(sp._mutex) {
    AddCount();
  }

  ~SharedPtr() { Release(); }

  void Release() {
    if (--(*_pCount) == 0) {
      delete _pCount;
      D()(_ptr);
    }
  }

  void AddCount() {
    std::cout << "pCount++" << std::endl;
    _mutex->lock();
    (*_pCount)++;
    _mutex->unlock();
  }

  SharedPtr<T> &operator=(const SharedPtr<T> &sp) {
    if (sp._ptr == _ptr) {
      return *this;
    } else {
      Release();
      _ptr = sp._ptr;
      _pCount = sp._pCount;
      AddCount();
      return *this;
    }
  }

  T &operator*() { return *_ptr; }

  T *operator->() { return _ptr; }

  SharedPtr(SharedPtr<T> &&sp) noexcept
      : _ptr(sp._ptr), _pCount(sp._pCount), _mutex(sp._mutex) {
    sp._ptr = nullptr;
    sp._pCount = nullptr;
    sp._mutex = nullptr;
  }

  SharedPtr<T> &operator=(SharedPtr<T> &&sp) noexcept {
    if (this != sp) {
      Release();
      _ptr = sp._ptr;
      _pCount = sp._pCount;
      _mutex = sp._mutex;
      sp._ptr = nullptr;
      sp._pCount = nullptr;
      sp._mutex = nullptr;
    }
    return *this;
  }

 private:
  T *_ptr;
  int *_pCount;
  std::mutex *_mutex;
};

void test_shared_ptr1() {
  SharedPtr<A, Delete<A>> sp1(new A);
  SharedPtr<int, DeleteArray<int>> n3(new int[5]);
  SharedPtr<A> sp2(sp1);
  SharedPtr<A> sp3(sp1);

  sp1->_a1++;
  sp1->_a2++;
  std::cout << sp2->_a1 << ":" << sp2->_a2 << std::endl;
  sp2->_a1++;
  sp2->_a2++;
  std::cout << sp1->_a1 << ":" << sp1->_a2 << std::endl;

  SharedPtr<A> sp5(new A);
  SharedPtr<A> sp6(sp5);
  sp1 = sp5;
  sp2 = sp5;
  sp3 = sp5;

  // 自己给自己赋值
  std::cout << "自己给自己赋值" << std::endl;
  SharedPtr<int> sp4(new int);
  sp4 = sp4;
  sp1 = sp5;  // 这也属于自己给自己赋值，因为管理的是完全相同的资源
              // 虽然不会出错，但没有必要

  // 自定义的删除器也可以使用 lambda
  auto customDeleter = [](int *ptr) { delete[] ptr; };
  SharedPtr<int, decltype(customDeleter)> n3(new int[5]);
  // SharedPtr<int, decltype(auto) [](int* ptr) { delete[] ptr; }> n3(new
  // int[5]);
}
