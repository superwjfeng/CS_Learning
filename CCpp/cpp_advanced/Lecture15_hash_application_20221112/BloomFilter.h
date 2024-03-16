#pragma once

// N表示准备要映射N个值
template <size_t N, class K, class Hash1, class Hash2, class Hash3>
class BloomFilter {
 public:
  void Set(const K& key) {
    size_t hash1 =
        Hash1()(key) %
        (_ratio *
         N);  // 匿名对象仿函数得到的hash值可能超出范围，要用除留余数法让它落到合法范围内
    _bits.set(hash1);
    size_t hash2 = Hash2()(key) % (_ratio * N);
    _bits.set(hash2);
    size_t hash3 = Hash3()(key) % (_ratio * N);
    _bits.set(hash3);
  }

  bool Test(const K& key) {
    size_t hash1 = Hash1()(key) % (_ratio * N);
    if (!_bits.test(hash1))  // 有一个为0，就可以判断不在了，判断不在是准确的
      return false;
    size_t hash2 = Hash2()(key) % (_ratio * N);
    if (!_bits.test(hash2))  // 有一个为0，就可以判断不在了
      return false;
    size_t hash3 = Hash3()(key) % (_ratio * N);
    if (!_bits.test(hash3))  // 有一个为0，就可以判断不在了
      return false;

    return true;  // 可能存在误判
  }

 private:
  const static size_t _ratio =
      5;  // ratio是根据公式算出来的，3个哈希函数，每个插入值给5个比特位
  bitset<_ratio * N> _bits;
};
