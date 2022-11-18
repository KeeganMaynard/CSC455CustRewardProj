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
  vector<string> readProducts(string);

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

// Function to read the file and fill up the vector
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

// parse data from file into vector
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

  // line = line.substr(line.find_first_of(' ') + 1, line.length());
  // loadNum = line.substr(0, line.length());
  // loadProd.setNumProducts(stoi(loadNum));
  loadProd.setNumProducts(20);

  products.push_back(loadProd);
}

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

vector<string> product::readProducts(string f)
{
  fstream file;
  string line;
  file.open(f);
  vector<string> lines;
  file.open(f);
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  return lines;
}

// add new product to inventory
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

// removes existing product from inventory
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

// finds product to be removed from vector
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

// finds product to be returned to the caller
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

// get user input
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

string product::enterProductName()
{
  string name;

  cout << "Enter Product Name: ";
  getline(cin, name);
  return name;
}

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

// validate product id
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

// validate inventory is postive integer
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

// validate id is unique
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
// append the last product in the vector to the txt file
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
// log products to products.txt

// string productID;
// string productName;
// string productPrice;
// int numProducts;
string product::toString2(product prod)
{
  cout << prod.getProductID() << endl;
  cout << prod.getName() << endl;
  cout << prod.getProductPrice() << endl;

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
  }
}

#endif