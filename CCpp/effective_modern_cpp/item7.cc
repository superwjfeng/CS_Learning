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

void test_item7() {
  A a = 10;
}

int main() {
  A a = 10;
  return 0;
}