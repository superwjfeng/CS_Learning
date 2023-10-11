#include <iostream>

int main() {
  int x = 10;

  // 捕获变量x，参数列表中没有形参
  auto captureVar = [x]() {
    // 可以访问x的值，但不能修改它
    std::cout << "Captured variable: " << x << std::endl;
  };

  // 参数列表中有形参y
  auto withParam = [](int y) {
    // 参数y可以被访问，但不是捕获的外部变量
    std::cout << "Parameter: " << y << std::endl;
  };

  captureVar(); // 调用捕获变量的lambda
  withParam(x); // 调用带参数的lambda，将x传递给y
  int y = 3;

  std::find_if(x, y, 3);
  return 0;
}