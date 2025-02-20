#include "movie.h"
#include <iostream>
#include "util.h"
using namespace std;

Movie::Movie(string name, double price, int qty, string genre, string rating) : Product("movie", name, price, qty), genre_(genre), rating_(rating){}

set<string> Movie::keywords() const {

  set<string> words = parseStringToWords(name_);
  set<string> wordsGenre = parseStringToWords(genre_);

  set<string> combination = setUnion(words, wordsGenre);
  combination.insert(rating_);
  return combination;
}

string Movie::displayString() const{

  return  name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";

}

void Movie::dump(std::ostream& os) const {
  os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}


