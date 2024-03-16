#pragma once

namespace wjf {
template <size_t N>  // Nontype
class bit_set {
 public:
  bit_set() {
    _bits.resize(
        N / 8 + 1,
        0);  // N是要开的位图的长度，一个char有一字节8位，多开一字节防止整除截断
  }

  void set(size_t x) {     // 设置bit为1
    size_t i = x / 8;      // 在第几个char上
    size_t j = x % 8;      // 在char的第几位上
    _bits[i] |= (1 << j);  // 00000001左移j位后进行或运算
    // 适用于小端机和大端机，因为 "<<" 的意思是往高位移动，而不是左移
  }

  void reset(size_t x) {  // 设置bit为0
    size_t i = x / 8;
    size_t j = x % 8;
    _bits[i] &= ~(1 << j);
  }

  bool test(size_t x) {  // 判断x在不在
    size_t i = x / 8;
    size_t j = x % 8;
    return _bits[i] & (1 << j);
  }

 private:
  vector<char> _bits;
};

void test_set1() {
  bit_set<100> bs1;
  bs1.set(8);
  bs1.set(9);
  bs1.set(20);

  cout << bs1.test(8) << endl;
  cout << bs1.test(9) << endl;
  cout << bs1.test(20) << endl;

  bs1.reset(8);
  bs1.reset(9);
  bs1.reset(20);
}

void test_set2() {
  bit_set<-1> bs1;
  // bit_set<0xffffffff> bs2;
}

template <size_t N>
class twobitset {
 public:
  // 00：0次； 01：1次； 10：2次； 11：3次及以上
  void set(size_t x) {
    bool inset1 = _bs1.test(x);
    bool inset2 = _bs2.test(x);
    // 00
    if (inset1 == false && inset2 == false) {
      //-> 01
      _bs2.set(x);
    } else if (inset1 == false && inset2 == true) {
      //-> 10
      _bs1.set(x);
      _bs2.reset(x);
    } else if (inset1 == true && inset2 == false) {
      _bs1.set(x);
      _bs2.set(x);
    }
  }

  void print_once_num() {
    for (size_t i = 0; i < N; i++) {
      if (_bs1.test(i) == false && _bs2.test(i) == true) {
        cout << i << endl;
      }
    }
  }

 private:
  bit_set<N> _bs1;
  bit_set<N> _bs2;
};

void test_set3() {
  int a[] = {3,  4, 5,  2,  3,  4,  4,  4, 4, 12, 77, 65,
             44, 4, 44, 99, 33, 33, 33, 6, 5, 34, 12};

  twobitset<100> bs;
  for (auto e : a) {
    bs.set(e);
  }

  bs.print_once_num();
}
}  // namespace wjf
