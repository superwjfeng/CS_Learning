#ifndef HOMEWORK_PRIME15_QUOTE_H_
#define HOMEWORK_PRIME15_QUOTE_H_

#include <string>
using std::string;

class Quote {
public:
  Quote() = default;
  Quote(const string &book, double sales_price)
    : book_no_(book), price_(sales_price)
  {}
  virtual ~Quote() = default;
public:
  string get_isbn() const { return book_no_; }
  // 返回给定数量n本书籍的销售总额
  virtual double net_price(std::size_t n) const { return n * price_; }
protected:
  double price_ = 0.0;                          // 代表普通状态下不打折的价格
private:
  string book_no_;                              // 书籍的ISBN编号
};
#endif
