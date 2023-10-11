#ifndef HOMEWORK_PRIME15_BULK_QUOTE_H_
#define HOMEWORK_PRIME15_BULK_QUOTE_H_
#include "quote.h"

class BulkQuote : public Quote {
public:
  BulkQuote() = default;
  BulkQuote(const string &book, double p, 
            std::size_t qty, double disc)
    : Quote(book, p), min_qty_(qty), discount_(disc)
  {}
public:
  double net_price(std::size_t) const override;
private:
  std::size_t min_qty_ = 0;               // 通用则扣政策的最低购买量
  double discount_ = 0.0;                 // 以小数表示的折扣
};
#endif
