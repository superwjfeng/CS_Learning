#include <iostream>
using namespace std;

//// 无继承
//class Base {
//public:
//  virtual void func1() {
//    cout << "Base::func1()" << endl;
//  }
//  virtual void func2() {
//    cout << "Base::func2()" << endl;
//  }
//private:
//  int b_;
//};
//
//
//int main() {
//  Base b;
//  cout << endl;
//  return 0;
//}


//// 单继承
//class Base {
//public:
//  virtual void func1() {
//    cout << "Base::func1()" << endl;
//  }
//  virtual void func2() {
//    cout << "Base::func2()" << endl;
//  }
//private:
//  int b_;
//};
//
//class Derived : public Base {
//public:
//  virtual void func1() {
//    cout << "Derive::func1()" << endl;
//  }
//  virtual void func3() {
//    cout << "Derive::func3()" << endl;
//  }
//  void func4() {
//    cout << "Derive::func4()" << endl;
//  }
//private:
//  int d_;
//};
//
//int main() {
//  Base b;
//  Derived d1;
//  Derived d2;
//  cout << endl;
//  return 0;
//}

// 多继承
class Base1 {
public:
  virtual void func1() {
    cout << "Base1::func1()" << endl;
  }
  virtual void func2() {
    cout << "Base1::func2()" << endl;
  }
private:
  int b1_;
};

class Base2 {
public:
  virtual void func1() {
    cout << "Base2::func1()" << endl;
  }
  virtual void func2() {
    cout << "Base2::func2()" << endl;
  }
private:
  int b2_;
};

class Derived : public Base1, public Base2 {
public:
  virtual void func1() {
    cout << "Derive::func1()" << endl;
  }
  virtual void func3() {
    cout << "Derive::func3()" << endl;
  }
private:
  int d_;
};

int main() {
  Base1 b1;
  Base2 b2;

  Derived d;
  cout << endl;
  return 0;
}