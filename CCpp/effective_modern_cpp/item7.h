#ifndef EFFECTIVE_MODERN_CPP_ITEM7_H_
#define EFFECTIVE_MODERN_CPP_ITEM7_H_

#include <iostream>

class A {
public:
  A(int a) : a_(a) {
    std::cout << "A(int a)" << std::endl;
  }
  A(const A &a) {
    std::cout << "A(const A& a)" << std::endl;
  }
private:
  int a_ = 0;
};

#endif // !EFFECTIVE_MODERN_CPP_ITEM7_H_
