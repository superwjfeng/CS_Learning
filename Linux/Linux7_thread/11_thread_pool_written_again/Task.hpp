#include <iostream>

typedef void *(*CallBack)(void *);

class Parm {
  int id_;
};

class Task {
 public:
  void callback() { std::cout << "hello" << std::endl; }

 private:
  CallBack *callback_;
  Parm *parm_;
};