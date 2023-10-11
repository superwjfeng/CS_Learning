#ifndef HOMEWORK_PRIME16_BLOB_H_
#define HOMEWORK_PRIME16_BLOB_H_
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <stdexcept>

template<typename T> class Blob {
public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;
public:
  Blob()
    : data_(std::make_shared<std::vector<T>()) {}
  Blob(std::initializer_list<T> il)
    : data_(std::make_shared<std::vector<T>(il)) {}
  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }
  void push_back(const T &t) { data_->push_back(t); }
  void push_back(T &&t) { data_->push_back(std::move(t)); }
  void pop_back();
  T &back();
  T &operator[](size_type i);
private:
  void check(size_type i, const std::string &msg) const;
private:
  std::shared_ptr<std::vector<T>> data_;
};

template<typename T>
inline void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  data_->pop_back();
}

template<typename T>
inline T &Blob<T>::back() {
  check(0, "back on empty Blob");
  return data_->back();
}

template<typename T>
inline T &Blob<T>::operator[](size_type i) {
  check(i, "subscript out of range");
  return (*data)[i];
}

template<typename T>
inline void Blob<T>::check(size_type i, const std::string &msg) const {
  if (i >= data_->size())
    throw std::out_of_range(msg);
}

#endif
