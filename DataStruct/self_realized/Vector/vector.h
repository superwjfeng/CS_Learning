#pragma once
#include <assert.h>
#include <cstddef> // for size_t

namespace wjf {
template <class T> class vector {
public:
  typedef T *iterator;

  iterator begin() { return _start; }

  iterator end() { return _finish; }
  
  const iterator begin() const { return _start; }

  const iterator end() const { return _finish; }

  vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

  ~vector() {
    delete[] _start;
    _start = _finish = _end_of_storage = nullptr;
  }

  // const权限缩小同时适配普通和const对象
  size_t capacity() const { return _end_of_storage - _start; }

  size_t size() const { return _finish - _start; }

  T& operator[](size_t pos) {
    assert(pos < size());
    return _start[pos];
  }

  //const只读不写
  const T& operator[](size_t pos) const {
    assert(pos < size());
    return _start[pos];
  }

  void reserve(size_t n) {
    if (n > capacity()) {
      size_t sz = size(); //为后面保留sz，否则扩容后_start变了
      T *tmp = new T[n];
      if (_start) {
        // memcpy(tmp, _start, sizeof(T)*sz);
        for (size_t i = 0; i < sz; i++) {
          tmp[i] = _start[i];
        }
        delete[] _start; // 释放旧空间
      }
      _start = tmp; // 指向新空间
      _finish = _start + sz;
      _end_of_storage = _start + n;
    }
  }

  void resize(size_t n, const T &val = T()) {}

  T& front();

  T& back();

  void push_back(const T &x) {
    if (_finish == _end_of_storage) {
      reserve(capacity() == 0 ? 4 : capacity() * 2);
    }
    *_finish = x;
    _finish++;
  }

  void pop_back() {
    assert(_finish > _start);
    --_finish;
  }

  //pos前插入
  iterator insert(iterator pos, const T &x) {
    assert(pos >= _start && pos <= _finish);
    if (_finish == _end_of_storage) {//扩容
      // 迭代器失效问题
      // 扩容前计算pos和_start的相对位置，扩容后令原pos重新指向
      size_t len = pos - _start;
      reserve(capacity() == 0 ? 4 : capacity() * 2);
      pos = _start + len;
    }
    iterator end = _finish - 1;
    while (end >= pos) {
      *(end + 1) = *end;
      end--;
    }
    *pos = x;
    _finish++;
    return pos;
  }

  iterator erase(iterator pos) {
    assert(pos >= _start && pos <= _finish);
    //从前往后挪数据
    iterator begin = pos + 1;
    while (begin < _finish) {
      *(begin - 1) = *begin;
      begin++;
    }
    _finish--;
    return pos;
  }

private:
  iterator _start;
  iterator _finish;
  iterator _end_of_storage;
};
}; // namespace wjf
