#ifndef BOOK_H
#define BOOK_H

#include "product.h"


class Book : public Product {

public:
  Book(const std::string name, double price, int qty, std::string isbn, std::string author);

  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

private:
  std::string isbn_;
  std::string author_;

};

#endif