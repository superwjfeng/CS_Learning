#include <iostream>
#include <string>
using namespace std;

//const std::string &shorterString(const std::string &s1, const std::string &s2) {
//  return s1.size() <= s2.size() ? s1 : s2;
//}
//std::string &shorterString(std::string &s1, std::string &s2) {
//  std::cout << "non-const" << std::endl;
//  auto &r = shorterString(const_cast<const std::string &>(s1), // 给参数添加const
//    const_cast<const std::string &>(s2));
//  return const_cast<std::string &>(r);
//}
//
//int main() {
//  std::string s1{ "hello" };
//  std::string s2{ "hello2" };
//
//  std::string& s3 = shorterString(s1, s2);
//  s3[1] = '2';
//  std::cout << s3 << std::endl; // h2llo
//  std::cout << s1 << std::endl; // h2llo
//
//
//  int i = 2;
//  auto func = [](int i) {
//    if (i > 0) return i;
//    else return -i;
//  };
//
//  std::cout << func(i) << std::endl;
//
//  return 0;
//}

class A {
public:
  virtual void print() {
    cout << "A" << endl;
  }
};

class B : public A {
public:
  void print() {
    cout << "B" << endl;
  }
};

class C : public A {
public:
  void print() {
    cout << "C" << endl;
  }
};


int main() {
  B b;
  A *a = &b;
  a->print();

  int c = 2;
  const int d = 3;

  return 0;
}