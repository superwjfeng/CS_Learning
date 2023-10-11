#include <iostream>
#include <string>
#include <regex>

/*6.3, 6.4*/

/*
int fact(int val) {
  if (val < 0) return -1;
  int ret = 1;
  for (int i = 1; i <= val; i++) {
    ret *= i;
  }

  return ret;
}


int main() {
  int num;
  std::cin >> num;
  int ret = fact(num);
  std::cout << ret << std::endl;
  return 0;
}
*/

/*6.7*/
/*
unsigned int myCount() {
  static unsigned int cnt = -1;
  return ++cnt;
}

int main() {
  for (int i = 0; i < 10; i++) {
    std::cout << myCount() << std::endl;
  }

  return 0;
}
*/

/*6.10, 6.12*/
/*
void mySwap(int *p, int *q) {
  int tmp = *p;
  *p = *q;
  *q = tmp;
}

void mySWAP(int &p, int &q) {
  int tmp = p;
  p = q;
  q = tmp;
}

int main() {
  int p = 1, q = 2;
  std::cout << p << ":" << q << std::endl;
  mySwap(&p, &q);
  std::cout << p << ":" << q << std::endl;

  int a = 1, b = 2;
  std::cout << a << ":" << b << std::endl;
  mySWAP(a, b);
  std::cout << a << ":" << b << std::endl;
  return 0;
}
*/

/*6.21*/
/*
int swapIntPointer(const int a, const int *pb) {
  return a > *pb ? a : *pb;
}

int main() {
  int a = 2;
  int b = 3;
  std::cout << swapIntPointer(a, &b) << std::endl;
  return 0;
}
*/

/*6.25*/
/*
int main(int argc, char **argv) {
  std::string str;
  for (int i = 0; i < argc; i++) {
    str += argv[i];
  }
  std::cout << str << std::endl;
  return 0;
}
*/

using namespace std;

int main() {
  char userName[20] = "";
  while (1) {
    cout << "输入用户名:";
    cin >> userName;
    // 注意C++中 \ 变为 \\（转义）
    regex reg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    bool result = regex_match(userName, reg);
    //smatch result;
    //bool flag = regex_search(userName, result, regex("\\d+"));
    if (result == true) {
      cout << "输入的是有效邮箱！" << endl;
      break;
    }
    else {
      cout << "输入的不是邮箱!重新输入" << endl;
    }
  }
  return 0;
}
