#include <iostream>
#include <utility>

int main() {
  int a = 10;
  const int b = 2;
  int *aptr = &a;
  decltype(*aptr) b1; // *a 表达式返回的是左值引用，结果为int &
  decltype(&a) b2; // &a 表达式返回的是地址的右值引用， 结果为int
  decltype(std::move(a)) b3; // 将亡值，结果为int &&

  return 0;
}