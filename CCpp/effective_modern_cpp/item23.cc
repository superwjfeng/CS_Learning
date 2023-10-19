#include <iostream>
#include <utility>
using namespace std;

struct A {
  A(int value) : b(value) { std::cout << "create" << std::endl; }
  A(const A &value) {
    std::cout << "copy" << std::endl;
    b = value.b;
  }
  A(A &&value) {
    std::cout << "move" << std::endl;
    b = value.b;
    value.b = 0;
  }

  int b;
};

void process(const A &lvalArg) { // 左值版本
  std::cout << "deal 1valArg" << std::endl;
}
void process(A &&rva1Arg) { // 右值版本
  std::cout << "deal rvalArg" << std::endl;
}
template<typename T> void logAndProcess(T &&param) {
  // process(param); // 一定调用左值版本
  // process(std::move(param)); // 一定调用右值版本 
  process(std::forward<T>(param)); // 实参用右值初始化时，转换为一个右值
}


int main() {
  A mm{ 10 };
  logAndProcess(mm);
  logAndProcess(std::move(mm));

  return 0;
}
