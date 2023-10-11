#ifndef HOMEWORK_PRIME7_SALES_DATA_H_
#define HOMEWORK_PRIME7_SALAS_DATA_H_

#include <string>
using std::string;

class SalesData {
public:
  string isbn() const {
    return this->book_no_;
  }
  SalesData& combine(const SalesData &rhs);
private:
  string book_no_;              // 书籍编号
  unsigned units_sold_ = 0;     // 销售量
  double selling_price_ = 0.0;  // 原始价格
  double sale_price_ = 0.0;     // 实售价格
  double discount_ = 0.0;       // 折扣
};
#endif
