#include "book.h"
#include <iostream>
#include "util.h"
using namespace std;

Book::Book(string name, double price, int qty, string isbn, string author) : Product("book", name, price, qty), isbn_(isbn), author_(author){}

set<string> Book::keywords() const {

  set<string> words = parseStringToWords(name_);
  set<string> wordsAuthor = parseStringToWords(author_);

  set<string> combination = setUnion(words, wordsAuthor);
  combination.insert(isbn_);
  return combination;
}

string Book::displayString() const{
  return  name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";

}

void Book::dump(std::ostream& os) const {
  os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}

