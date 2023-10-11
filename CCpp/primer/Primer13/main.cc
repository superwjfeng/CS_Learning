#include "str_vec.h"

template<typename T>
class NamedObject {
public:
  NamedObject(std::string &name, const T &value)
    : name_value_(name), object_value_(value)
  {}
  void operator=(const NamedObject &rhs) {
    name_value_ = rhs.name_value_;
  }
  // 假设没有自定义operator=
private:
  std::string &name_value_; // 现在是一个引用
  const T object_value_;    // 现在是一个常量
};

int main() {
  std::string newDog("Persephone");
  std::string oldDog("Satch");
  NamedObject<int> p(newDog, 2);
  NamedObject<int> s(oldDog, 36);
  p = s;
  return 0;
}