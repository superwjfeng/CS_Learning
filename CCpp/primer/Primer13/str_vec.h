#ifndef HOMEWORK_PRIME13_STR_VEC_H_
#define HOMEWORK_PRIME13_STR_VEC_H_

#include <iostream>
#include <string>
#include <memory>
using std::string;

class StrVec
{
public:
  StrVec()
    : elements_(nullptr)
    , first_free_(nullptr)
    , cap_(nullptr)
  {}
  StrVec(const StrVec &);
  StrVec &operator=(const StrVec &);
  ~StrVec() { free(); }
public:
  void push_back(const string &);
  void push_back(const string &&);
  size_t size() const { return first_free_ - elements_; }
  size_t capacity() const { return cap_ - elements_; }
  string *begin() const { return elements_; }
  string *end() const { return first_free_; }
private:
  std::allocator<string> alloc;
  void chk_n_alloc() {
    if (size() == capacity()) reallocate();
  }
  std::pair<string *, string *> alloc_n_copy (const string *, const string *);
  void free();
  void reallocate();         // 获得更多内存并拷贝已有元素
private:
  string *elements_;         // 指向分配的内存中的首元素
  string *first_free_;       // 指向最后一个实际元素之后的位置
  string *cap_;              // 指向分配的内存末尾之后的位置
};
#endif
