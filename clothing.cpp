#include "clothing.h"
#include <iostream>
#include "util.h"
using namespace std;

Clothing::Clothing(string name, double price, int qty, string size, string brand) : Product("clothing", name, price, qty), size_(size), brand_(brand){}

set<string> Clothing::keywords() const {

  set<string> words = parseStringToWords(name_);
  set<string> wordsBrand = parseStringToWords(brand_);

  set<string> combination = setUnion(words, wordsBrand);
  combination.insert(size_);
  return combination;
}

string Clothing::displayString() const{


  return  name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";

}

void Clothing::dump(std::ostream& os) const {
  os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}



