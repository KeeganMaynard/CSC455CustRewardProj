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

class product
{
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
  void shutdown();
  void parseData(string);

  // user input
  string enterProductID();
  string enterProductName();
  string enterProductPrice();
  int enterNumProducts();

  // input validation
  bool validID(string);
  bool validNumProduct(string);
  bool validPrice(string);

  // items to check that IDs are unique
  bool productIdUnique(string);
  vector<product> products;

  // string handling
  string toString2(product prod);
  product returnProduct(product prod, string id);
  void printProducts(product prod);
  void logProduct(int);

  // set
  void setProductID(string newID) { productID = newID; }
  void setProductName(string newName) { productName = newName; }
  void setProductPrice(string newPrice) { productPrice = newPrice; }
  void setNumProducts(int newNumProd) { numProducts = newNumProd; }

  // get
  string getProductID() { return productID; }
  string getName() { return productName; }
  string getProductName() { return productName; }
  string getProductPrice() { return productPrice; }
  int getNumProducts() { return numProducts; }
};

/* void product::initilize() - read from previous file to vector
parameters - N/A
return - void
*/
void product::initilize()
{
  ifstream pLog;
  pLog.open("products.txt");

  if (pLog.is_open())
  {
    string line;
    string temp;
    string buffer;
    while (getline(pLog, line))
    {
      // parse data gathered from line
      if (!line.empty()) // Break on empty line
      {
        temp = line.substr(line.find_last_of(' ') + 1, line.length());
        buffer = buffer + temp + " ";
      }
      else
      {
        parseData(buffer);
        temp = "";
        buffer = "";
      }
    }
    pLog.close();
  }
  else
  {
    cout << "Error reading products log file. Please ensure the file is "
            "attached to store product information."
         << endl;
  }
}

/* void product::parseDate(string) - parse product attributes and append onto vector
parameters - string of the line to parse into vector
return - void
*/
void product::parseData(string line)
{
  string loadID, loadName, loadPrice, loadNum;
  product loadProd;
  loadID = line.substr(0, line.find_first_of(' '));
  loadProd.setProductID(loadID);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadName = line.substr(0, line.find_first_of(' '));
  loadProd.setProductName(loadName);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadPrice = line.substr(0, line.find_first_of(' '));
  loadProd.setProductPrice(loadPrice);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadNum = line.substr(0, line.length());
  loadProd.setNumProducts(stoi(loadNum));
  // loadProd.setNumProducts(20);

  products.push_back(loadProd);
}
/* void product::shutdown() - clear file and reappend to remove old products
parameters - N/A
return - void
*/
void product::shutdown()
{
  // clear the text file to avoid duplicates
  ofstream logFile("products.txt");
  logFile.close();

  // write all products remaining
  for (int i = 0; i < products.size(); i++)
  {
    logProduct(i);
  }
}
/* void product::addProduct() - add new product to inventory
parameters - N/A
return - void
*/
void product::addProduct()
{
  product newProduct;

  newProduct.setProductID(enterProductID());
  newProduct.setProductName(enterProductName());
  newProduct.setProductPrice(enterProductPrice());
  newProduct.setNumProducts(enterNumProducts());

  products.push_back(newProduct);

  logProduct(products.size() - 1);

  cout << "\nproduct entered successfully\n\n";
}

/* void product::removeProduct() - remove product from inventory
parameters - N/A
return - void
*/
void product::removeProduct()
{
  string prodID;

  cout << "Enter product ID for product you wish to remove: ";
  getline(cin, prodID);

  if (!productIdUnique(prodID))
  {
    products.erase(products.begin() + findProduct(prodID));
  }
  else
  {
    cout << "Product ID does not exist ";
  }
}

/* int product::findProduct(string) - used by remove product so to find product entered by user for removal
parameters - string id of the product wanted for removal
return - int of vector index of removed product
*/
int product::findProduct(string id)
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].productID == id)
    {
      return i;
    }
    else
    {
      // continue through loop
    }
  }

  // Default return statement
  return -1;
}

/* product product::returnProduct() - returns product called by user
parameters - product prod string id
return - product
*/
product product::returnProduct(product prod, string id)
{
  for (int i = 0; i < prod.products.size(); i++)
  {
    if (prod.products[i].getProductID() == id)
    {
      return prod.products[i];
    }
    else
    {
      // continue through loop
    }
  }

  // Default return statement - will never be hit
  return prod;
}

/* string product::enterProductID() - asks user to input ID for product
parameters - N/A
return - string of product ID
*/
string product::enterProductID()
{
  string ID;

  cout << "Enter Product ID: ";
  getline(cin, ID);
  if (validID(ID))
  {
    return ID;
  }
  else
  {
    cout << "ID is invalid ";
    enterProductID();
  }
  return " ";
}

/* string product::enterProductName() - asks user to input Name for product
parameters - N/A
return - string of product Name
*/
string product::enterProductName()
{
  string name;

  cout << "Enter Product Name: ";
  getline(cin, name);
  return name;
}

/* string product::enterProductPrice() - asks user to input Price for product
parameters - N/A
return - string of product Price
*/
string product::enterProductPrice()
{
  string price;

  cout << "Enter Product Price: ";
  getline(cin, price);

  if (validPrice(price))
  {
    return price;
  }
  else
  {
    cout << "enter price in 000.00 format" << endl;
    enterProductPrice();
  }
  return " ";
}

/* int product::enternumProducts() - asks user to input quantity of product
parameters - N/A
return - int of quantity of product
*/
int product::enterNumProducts()
{
  string products;

  cout << "Enter Quantity of Product : ";
  getline(cin, products);
  if (validNumProduct(products))
  {
    return stoi(products);
  }
  else
  {
    cout << "Quantity of Product Invalid ";
    enterNumProducts();
  }

  // Default return statement - will never be hit
  return 1;
}

/* bool product::ValidID() - validates product ID
parameters - string id to be validated
return - bool T if id is valid
*/
bool product::validID(string id)
{
  if (productIdUnique(id))
  {
    if (regex_match(id, regex("^[P][0-9][0-9][0-9][0-9][0-9]$")))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

/* bool product::ValidPrice() - validates product Price
parameters - string p to be validated
return - bool T if id is valid
*/
bool product::validPrice(string p)
{
  if (regex_match(p, regex("^[0-9][0-9][0-9][.][0-9][0-9]$")) || regex_match(p, regex("^[0-9][0-9][.][0-9][0-9]$")) || regex_match(p, regex("^[0-9][.][0-9][0-9]$")))
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* bool product::ValidNumProducts() - validates product quantity
parameters - string p to be validated
return - bool T if id is valid
*/
bool product::validNumProduct(string p)
{
  for (int i = 0; i > p.length(); i++)
  {
    if (isdigit(p[i]))
    {
    }
    else
    {
      return false;
    }
  }
  if (stoi(p) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* bool product::productIdUnique() - validates product ID is unique
parameters - string id to be validated
return - bool T if id is valid
*/
bool product::productIdUnique(string id)
{
  for (int i = 0; i < products.size(); i++)
  {
    if (products[i].productID == id)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  // Default return statement - will never be hit
  return true;
}

/* void product::logProduct() - logs product info into "products.txt" file
parameters - int pNum to specifiy index of products vector to be logged
return - void
*/
void product::logProduct(int pNum)
{
  string &productID = products[pNum].productID;
  string &productName = products[pNum].productName;
  string &productPrice = products[pNum].productPrice;
  int &numProducts = products[pNum].numProducts;

  // open the log file and set to append data
  ofstream plog;
  plog.open("products.txt", ios::app);

  plog << "product " << pNum << " ID " << productID << endl;
  plog << "product " << pNum << " NAME " << productName << endl;
  plog << "product " << pNum << " PRICE " << productPrice << endl;
  plog << "product " << pNum << " QUANTITY " << numProducts << "\n\n";

  plog.close();
}

/* string product::toString2() - returns string of product
parameters - product to print
return - string of product info
*/
string product::toString2(product prod)
{
  cout << prod.getProductID() << endl;
  cout << prod.getName() << endl;
  cout << prod.getProductPrice() << endl;
  cout << prod.getNumProducts() << endl;

  return "";
}

void product::printProducts(product prod)
{
  cout << "print products ran" << endl;
  for (int i = 0; i < prod.products.size(); i++)
  {
    cout << prod.products[i].getProductID() << endl;
    cout << prod.products[i].getName() << endl;
    cout << prod.products[i].getProductPrice() << endl;
    cout << prod.products[i].getNumProducts() << endl;
  }
}

#endif