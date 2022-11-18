/*Transaction class - will connect with mainMenu.cpp
    used to house transaction data and will write to "transaction.txt"
*/
#pragma
#define TransactionManager_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "customerRegistration.h"
#include "productManagement.h"
#include "rewardManagement.h"

using namespace std;

class transaction {
 public:
  string transactionID;
  string userID;
  vector<string> productIDs;
  float totalAmount;
  int rewardPoints;
  vector<transaction> transactions;
  virtual string toString(vector<string> ids);
  transaction() {}

  transaction(string tID, string uID, vector<string> pIDs, float tAmount,
              int rPoints) {
    transactionID = tID;
    userID = uID;
    productIDs = pIDs;
    totalAmount = tAmount;
    rewardPoints = rPoints;
  }

  // Basic getters and setters for the objects attributes
  string getTransactionID() { return transactionID; }

  string getUserID() { return userID; }

  vector<string> getProductIDs() { return productIDs; }

  float getTotalAmount() { return totalAmount; }

  int getRewardPoints() { return rewardPoints; }

  void setTransactionID(string id) { transactionID = id; }

  void setUserID(string id) { userID = id; }

  void setTotalAmount(float amount) { totalAmount = amount; }
  void setProductIDs(vector<string> ids) { productIDs = ids; }
  void setRewardPoints(int rPoints) { rewardPoints = rPoints; }

  int completePurchase(customer cust, vector<product> &tempProds);
  vector<string> readFile(string file);
  vector<string> processProductIDs(string line);
  vector<transaction> createTransactions(vector<string> lines);
  void writeTransactions(vector<transaction> transactions);
  void shopping(customer &cust, product &prod);
  bool validateQuantity(product prod, int quantity);
};

vector<string> transaction::readFile(string file) {
  fstream myFile;
  string line;
  myFile.open(file);
  vector<string> lines;
  myFile.open(file);
  while (getline(myFile, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> transaction::processProductIDs(string line) {
  string s;
  string tmp;
  stringstream ss(s);
  vector<string> pIDs;
  while (getline(ss, tmp, ',')) {
    pIDs.push_back(tmp);
  }
  return pIDs;
}

vector<transaction> transaction::createTransactions(vector<string> lines) {
  // create a temporary transaction object
  transaction t;
  // grab the  amount of transactions within the file, if we know each block of
  // transactions is 6 lines long we can take the file size % 6 to roughly get
  // the amount of store transactions, this is technically depreciated as its
  // not used
  int transactionCount = lines.size() % 6;
  for (int j = 0; j <= lines.size();
       j += 6) {  // moving 6 lines at a time to get each block of transaction
    // setting the temporary transactions id
    t.transactionID = lines[j];
    // setting the temporary transactions userID
    t.userID = lines[j + 1];
    // setting the tempory transactions productIDs
    t.productIDs = processProductIDs(lines[j + 2]);
    // set the temporyt transactions total amount
    t.totalAmount = stof(lines[j + 3]);
    // setting the tempory transactions reward points
    t.rewardPoints = stoi(lines[j + 4]);
    // pushing to the main files transactions vector
    transactions.push_back(t);
  }
  // returning the vector that was pushed too, technically not necessary but
  // could be useful in situations
  return transactions;

  // each time this function is run it creates a new temporary transaction
  // object then pushes it to the permanent transaction objects vector of
  // transactions within the main file
}

string transaction::toString(vector<string> ids) {
  string finalString = "";
  for (int i = 0; i < ids.size(); i++) {
    if (i != ids.size() - 1) {
      finalString += ids[i] + ",";
    } else {
      finalString += ids[i];
    }
  }
  cout << finalString << endl;
  return finalString;
}

void transaction::writeTransactions(vector<transaction> transactions) {
  fstream myFile;
  cout << "writeTransactions ran" << endl;
  myFile.open("transactions.txt", ios::app);

  for (int i = 0; i < transactions.size(); i++) {
    myFile << "Transaction id: " << transactions[i].getTransactionID() << endl;
    myFile << "userID: " << transactions[i].getUserID() << endl;
    myFile << "Product Ids: " << toString(transactions[i].productIDs) << endl;
    myFile << "Total transaction amount: " << transactions[i].totalAmount
           << endl;
    myFile << "Reward Points: " << transactions[i].rewardPoints << endl;
    myFile << endl;
  }
  myFile.close();
}

void transaction::shopping(customer &cust, product &prod) {
  string custUN, prodId;
  vector<product> tempProds;
  bool play = true;
  bool notDone = true;
  while (play) {
    cout << "Enter your username: ";
    cin >> custUN;
    if (cust.custUNPresent(custUN)) {
      for (int i = 0; i < cust.customers.size(); i++) {
        if (custUN == cust.customers[i].getUserName()) {
          customer &tempCust = cust.customers[i];
          prod.printProducts(prod);
          while (notDone) {
            cout << "Enter the productId's you'd like to purchase, "
                    "enter 'q' to stop entering Ids: ";
            cin >> prodId;
            if (prodId.compare("q")) {
              tempProds.push_back(prod.returnProduct(prod, prodId));
            } else {
              notDone = false;
            }
          }
          int rPoints = completePurchase(tempCust, tempProds);
          tempCust.setPoints(rPoints);
          play = false;
        } else {
          continue;
        }
      }
      // prod.printProducts(prod);
      // while (notDone) {
      //   cout << "Enter the productId's you'd like to purchase, "
      //           "enter 'q' to stop entering Ids: ";
      //   cin >> prodId;
      //   if (prodId.compare("q")) {
      //     tempProds.push_back(prod.returnProduct(prod, prodId));
      //   } else {
      //     notDone = false;
      //   }
      // }
      // int rPoints = completePurchase(tempCust, tempProds);
      // tempCust.setPoints(rPoints);
    } else {
      cout << "The Username does not exist! Enter again." << endl;
      play = true;
    }
  }
}

int transaction::completePurchase(customer cust, vector<product> &tempProds) {
  transaction trans;
  int rPoints = 0;
  int quantity;
  trans.transactionID = to_string(100000 + (rand() % 999999));

  trans.setUserID(cust.getCustID());
  for (int i = 0; i < tempProds.size(); i++) {
    cout << "Enter the quantity of " + tempProds[i].getProductID() + ": ";
    cin >> quantity;
    if (validateQuantity(tempProds[i], quantity)) {
      trans.productIDs.push_back(tempProds[i].getProductID());
      trans.totalAmount += stoi(tempProds[i].getProductPrice()) * quantity;
    } else {
      continue;  //? Gotta add stuff to this
    }
  }
  rPoints = cust.getPoints() + trans.totalAmount / 5;
  trans.rewardPoints = rPoints;
  transactions.push_back(trans);
  writeTransactions(transactions);
  return rPoints;
}

bool transaction::validateQuantity(product prod, int quantity) {
  if (quantity > prod.getNumProducts()) {
    return false;
  } else {
    return true;
  }
}