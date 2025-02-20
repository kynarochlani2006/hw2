#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <deque>
#include <map>
#include <iostream>

class MyDataStore : public DataStore{

public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  User* getUser(std::string uname);
  std::deque<Product*>& getUsersCart(std::string& username);
  void dump(std::ostream& ofile);

private: 
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::deque<Product*>> carts;

};

#endif