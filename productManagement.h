/*Product management class
    -author is Sky
*/
#ifndef PRODUCTMANAGMENT_H
#define PRODUCTMANAGMENT_H
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

class product {
 private:
  string productID;
  string productName;
  string productPrice;
  int numProducts;

 public:
  product(){};
  void initilize();

  // adding and removing products
  void addProduct();
  void removeProduct();
  int findProduct(string);

  // user input
  string enterProductID();
  string enterProductName();
  string enterProductPrice();
  int enterNumProducts();

  // input validation
  bool validID(string);
  bool validNumProduct(int);

  // items to check that IDs are unique
  bool productIdUnique(string);
  vector<product> products;

  void logProduct(product &);

  // set
  void setProductID(string newID) { productID = newID; }
  void setProductName(string newName) { productName = newName; }
  void setProductPrice(string newPrice) { productPrice = newPrice; }
  void setNumProducts(int newNumProd) { numProducts = newNumProd; }

  // get
  string getProductID() { return productID; }
  string getProductName() { return productName; }
  string getProductPrice() { return productPrice; }
  int getNumProducts() { return numProducts; }
};

// add new product to inventory
void product::addProduct() {
  product newProduct;

  newProduct.setProductID(enterProductID());
  newProduct.setProductName(enterProductName());
  newProduct.setProductPrice(enterProductPrice());
  newProduct.setNumProducts(enterNumProducts());

  products.push_back(newProduct);

  logProduct(newProduct);
}

// removes existing product from inventory
void product::removeProduct() {
  string prodID;

  cout << "Enter product ID for product you wish to remove: ";
  getline(cin, prodID);

  if (!productIdUnique(prodID)) {
    products.erase(products.begin() + findProduct(prodID));
  } else {
    cout << "Product ID does not exist ";
  }
}

// finds product to be removed from vector
int product::findProduct(string id) {
  for (int i = 0; i < products.size(); i++) {
    if (products[i].productID == id) {
      return i;
    } else {
      // continue through loop
    }
  }

  // Default return statement - will never be hit
  return 0;
}

// get user input
string product::enterProductID() {
  string ID;

  cout << "Enter Product ID: ";
  getline(cin, ID);
  if (validID(ID)) {
    return ID;
  } else {
    cout << "ID is invalid ";
    enterProductID();
  }

  // Default return statement - will never be hit
  return "Unable to enter valid product ID";
}

string product::enterProductName() {
  string name;

  cout << "Enter Product Name: ";
  cin >> name;
  return name;
}

string product::enterProductPrice() {
  string price;

  cout << "Enter Product Price: ";
  getline(cin, price);
  return price;
}

int product::enterNumProducts() {
  int products;

  cout << "Enter Quantity of Product : ";
  cin >> products;
  if (validNumProduct(products)) {
    return products;
  } else {
    cout << "Quantity of Product Invalid ";
    enterNumProducts();
  }

  // Default return statement - will never be hit
  return 1;
}

// validate product id
bool product::validID(string id) {
  if (productIdUnique(id)) {
    if (regex_match(id, regex("^[P][0-9][0-9][0-9][0-9][0-9]$"))) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// validate inventory is postive integer
bool product::validNumProduct(int p) {
  if (isdigit(p)) {
    if (p > 0) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// validate id is unique
bool product::productIdUnique(string id) {
  for (int i = 0; i < products.size(); i++) {
    if (products[i].productID == id) {
      return false;
    } else {
      return true;
    }
  }

  // Default return statement - will never be hit
  return true;
}

// log products to products.txt
void product::logProduct(product &p) {
  ofstream plog("products.txt");
  plog << "product " << products.size() << " " << p.getProductID() << endl;
  plog << "product " << products.size() << " " << p.getProductName() << endl;
  plog << "product " << products.size() << " $" << p.getProductPrice() << endl;
  plog << "product " << products.size() << " " << p.getNumProducts()
       << " quantity in store" << endl;

  plog.close();
}
#endif