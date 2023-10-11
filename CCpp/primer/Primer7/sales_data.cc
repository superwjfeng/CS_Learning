#include "sales_data.h"

SalesData& SalesData::combine(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  sale_price_ = (rhs.sale_price_ * rhs.units_sold_ + sale_price_ * units_sold_)
                  / (rhs.units_sold_ + units_sold_);
  if (selling_price_ != 0) {
    discount_ = sale_price_ / selling_price_;
  }
  return *this;
}
