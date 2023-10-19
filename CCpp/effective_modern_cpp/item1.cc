#include <iostream>
#include <utility>

template <typename T>
//void f(T param) { std::cout << param << std::endl; }
//void f(T *param) { std::cout << param << std::endl; }
//void f(T &param) { std::cout << param << std::endl; }
//void f(const T param) { std::cout << param << std::endl; } // 与 T 等价
void f(const T* param) { std::cout << param << std::endl; }
//void f(const T& param) { std::cout << param << std::endl; }
//void f(T* const param) { std::cout << param << std::endl; } // 与 T* 等价
//void f(const T* const param) { std::cout << param << std::endl; } // 与const T* 等价

void func(int, int) {}
int func2(int) {return 10;}

using F=int(int);


int main() {
  int a = 10;
  f(a);
  int *aptr = &a;
  f(aptr);
  int &aref = a;
  f(aref);
  int &&arref = std::move(a); // 右值引用仍是左值，引用性被忽略
  f(arref);

  const int ca = 20;
  f(ca);
  const int *captr = &ca;
  f(captr);
  const int &caref = ca;
  f(caref);
  const int &&carref = std::move(ca);
  f(carref);
  int *const acptr = &a;
  f(acptr);
  const int *const cacptr = &a;
  f(cacptr);


  int array[2] = {0, 1};
  f(array);
  const char aaa[12] = "hello world";
  f(aaa);
  int (*arrayPtr)[2] = &array;
  int (&arrayRef)[2] = array;

  func;
  void (*funcPtr)(int, int) = func;
  void (&funcRef)(int, int) = func;

  return 0;
}