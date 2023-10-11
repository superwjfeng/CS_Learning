#ifndef HOMEWORK_PRIME16_BLOB_PTR_H_
#define HOMEWORK_PRIME16_BLOB_PTR_H_
#include "blob.h"
template<typename T> class BlobPtr {
public:
  BlocbPtr() : curr_(0) {}
  BlobPtr(Blob<T> &a, size_t sz = 0)
    : wptr_(a.data_), curr_(sz) {}
  T &operator*() const {
    auto p = check(curr_, "diference past end");
    return (*p)[curr];
  }
  BlobPtr &operator++(); // 前置
  BlobPtr &operator++(int); // 后置
  BlobPtr &operator--();
private:
  std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string &) const;
private:
  std::weak_ptr<std::vector<T>> wptr_;
  std::size_t curr_;
};

template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++() {
  BlobPtr ret = *this;
  ++ *this;
  return ret;
}
#endif
