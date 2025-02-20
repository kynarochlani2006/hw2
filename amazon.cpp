#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <deque>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "mydatastore.h"
#include "util.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if( cmd == "ADD"){
              string username;
              int num; 

              if (ss >> username >> num) {
                User* u = ds.getUser(username);
                if(!u){
                  cout << "Invalid request" << endl;
                } else if(num <= 0 || num > hits.size()){
                  cout << "Invalid request" << endl;
                } else {
                  Product* p = hits[num - 1];
                  ds.getUsersCart(username).push_back(hits[num - 1]);
                  
                }
              } else {
                cout << "Invalid request" << endl;
              }
            } else if( cmd == "VIEWCART") {
              string username;

              if(ss >> username){
                User* u = ds.getUser(username);
                if(!u){
                  cout << "Invalid username" << endl;
                } else {
                  if(!ds.getUsersCart(username).empty()){
                    for(size_t i = 0; i < ds.getUsersCart(username).size(); i++){
                      cout << "Hit " << setw(3) << i + 1 << endl;
                      cout << ds.getUsersCart(username)[i]->displayString() << endl;
                    }
                  }
                }
              } else {
                cout << "Invalid username" << endl;
              }
            } else if( cmd == "BUYCART" ){
              string username;

              if(ss >> username){
                User* u = ds.getUser(username);
                if(!u){
                  cout << "Invalid username" << endl;
                } else {
                  deque<Product*>& cart = ds.getUsersCart(username);
                  deque<Product*> reaminCart;

                  while(!cart.empty()){
                    Product* prod = cart.front();
                    cart.pop_front();

                    if(prod->getQty() > 0 && u->getBalance() >= prod->getPrice()){
                      u->deductAmount(prod->getPrice());
                      prod->subtractQty(1);
                    } else {
                      reaminCart.push_back(prod);
                    }
                  }
                  ds.getUsersCart(username) = reaminCart;
                }
              }
              else {
                cout << "Invalid username" << endl;
              }

            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
