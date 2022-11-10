/*Product management class - will connect with mainMenu.cpp
    shop manager should be able to add and remove products from inventory
    - product id:
        - must start with a 'P' followed by a 5 digit number
            - ex: P01234
        - must be unit (cannot already exist)
    - product name (description)
    - product price:
        - do we want to store it in the txt file with the $ attached or attach it whenever we retrieve the value?
    - the number of products currently in stock in the store:
        - must be a positive number
    - all products information must be saved in a file named "products.txt"
        - check assignment.pdf for format
        - only write to file AFTER user input has been validated
    - will need to split all inputs into their own functions
        - make logging its own function
        - make validation its own function
    - will need to be able to read PREVIOUS RECORDS
*/
#ifndef PRODUCTMANAGMENT_H
#define PRODUCTMANAGMENT_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
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
void product::addProduct()
{
    product newProduct;

    newProduct.setProductID(enterProductID());
    newProduct.setProductName(enterProductName());
    newProduct.setProductPrice(enterProductPrice());
    newProduct.setNumProducts(enterNumProducts());

    products.push_back(newProduct);

    logProduct(newProduct);
}

// removes existing product from inventory
void product::removeProduct()
{
    string prodID;

    cout << "Enter product ID for product you wish to remove: ";
    cin >> prodID;

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
}

// get user input
string product::enterProductID()
{
    string ID;

    cout << "Enter Product ID: ";
    cin >> ID;
    if (validID(ID))
    {
        return ID;
    }
    else
    {
        cout << "ID is invalid ";
        enterProductID();
    }
}

string product::enterProductName()
{
    string name;

    cout << "Enter Product Name: ";
    cin >> name;
    return name;
}

string product::enterProductPrice()
{
    string price;

    cout << "Enter Product Price: ";
    cin >> price;
    return price;
}

int product::enterNumProducts()
{
    int products;

    cout << "Enter Quantity of Product : ";
    cin >> products;
    if (validNumProduct(products))
    {
        return products;
    }
    else
    {
        cout << "Quantity of Product Invalid ";
        enterNumProducts();
    }
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

// validate inventory is postive integer
bool product::validNumProduct(int p)
{
    if (isdigit(p))
    {
        if (p > 0)
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
}

// log products to products.txt
void product::logProduct(product &p)
{
    ofstream plog("products.txt");
    plog << "product " << products.size() << " " << p.getProductID() << endl;
    plog << "product " << products.size() << " " << p.getProductName() << endl;
    plog << "product " << products.size() << " $" << p.getProductPrice() << endl;
    plog << "product " << products.size() << " " << p.getNumProducts() << " quantity in store" << endl;

    plog.close();
}
#endif