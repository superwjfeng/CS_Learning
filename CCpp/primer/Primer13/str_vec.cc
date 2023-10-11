#include "str_vec.h"

StrVec::StrVec(const StrVec &s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements_ = newdata.first;
  first_free_ = cap_ = newdata.second;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free(); // 自赋值问题
  elements_ = data.first;
  first_free_ = cap_ = data.second;
  return *this;
}

void StrVec::push_back(const string &s) {
  chk_n_alloc();
  alloc.construct(first_free_++, s);
}

void StrVec::push_back(const string &&s) {
  chk_n_alloc();
  alloc.construct(first_free_++, std::move(s));
}

std::pair<string *, string *> StrVec::alloc_n_copy
                (const string *b, const string *e) {
  auto data = alloc.allocate(e - b); // end - begin
  return { data, std::uninitialized_copy(b, e, data) };
}

void StrVec::free() {
  if (elements_) {
    for (auto p = first_free_; p != elements_;)
      alloc.destroy(--p);
    alloc.deallocate(elements_, cap_ - elements_);
  }
}

void StrVec::reallocate() {
  auto newcapacity = size() ? 2 * size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  auto dest = newdata;
  auto elem = elements_;
  for (size_t i = 0; i != size(); i++)
    alloc.construct(dest++, std::move(*elem++));
  free();
  elements_ = newdata;
  first_free_ = dest;
  cap_ = elements_ + newcapacity;
}
