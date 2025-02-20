#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
using namespace std;

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore() {
  for(Product* p : products_){
    delete p;
  }
  for(User* u : users_){
    delete u;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  carts[u->getName()] = deque<Product*>();
}

deque<Product*>& MyDataStore::getUsersCart(string& username){
  if(carts.find(username) != carts.end()){
    return carts[username];
  }

  deque<Product*> emptyCart;
  return emptyCart;
}


User* MyDataStore::getUser(std::string uname){

  for(User* u : users_){
    if(u->getName() == uname){
      return u;
    }
  }
  return nullptr;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){

  set<Product*> results; 

  for(string s : terms) {

    set<Product*> curr;

    for(Product* prod : products_){
      set<string> keyword = prod->keywords();

      for(string key : keyword){
        if(key == s){
          curr.insert(prod);
          break;
        }
      }
        
    }

    if(results.empty()){
      results = curr;
    } else {
      if(type == 0){
        results = setIntersection(results, curr);
      } else if (type == 1){
        results = setUnion(results, curr);
      }
    }
  }

  vector<Product*> finalVec;

  for(set<Product*>::iterator it = results.begin(); it != results.end(); ++it){
    finalVec.push_back(*it);
  }

  return finalVec;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << endl;
  for(Product* p : products_){
    p->dump(ofile);
  }

  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for(User* u : users_){
    u->dump(ofile);
  }

  ofile << "</users>" << endl;

}