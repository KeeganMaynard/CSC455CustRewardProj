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

  void completePurchase(customer &cust, product tempProd);

  void setTotalAmount(float amount) { totalAmount = amount; }
  void setProductIDs(vector<string> ids) { productIDs = ids; }
  void setRewardPoints(int rPoints) { rewardPoints = rPoints; }

  vector<string> readFile(string file);
  vector<string> processProductIDs(string line);
  vector<transaction> createTransactions(vector<string> lines);
  void writeTransactions(vector<transaction> &transactions);
  void shopping(customer &cust, product &prod);
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
  transaction t;
  vector<transaction> transactions;
  int transactionCount = lines.size() % 6;
  for (int j = 0; j <= lines.size(); j += 6) {
    t.transactionID = lines[j];
    t.userID = lines[j + 1];
    t.productIDs = processProductIDs(lines[j + 2]);
    t.totalAmount = stof(lines[j + 3]);
    t.rewardPoints = stoi(lines[j + 4]);
    transactions.push_back(t);
  }
  return transactions;
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

void transaction::writeTransactions(vector<transaction> &transactions) {
  fstream myFile;
  myFile.open("transactions.txt", ios::app);
  for (int i = 0; i <= transactions.size(); i++) {
    myFile << transactions[i].transactionID << endl;
    myFile << transactions[i].userID << endl;
    myFile << toString(transactions[i].productIDs) << endl;
    myFile << transactions[i].totalAmount << endl;
    myFile << transactions[i].rewardPoints << endl;
    myFile << endl;
  }
}

void transaction::shopping(customer &cust, product &prod) {
  string custUN, prodId;
  customer *tempCust;
  vector<product> tempProds;
  bool play = true;
  bool notDone = true;
  while (play) {
    cout << "Enter your username number: ";
    cin >> custUN;
    if (cust.custUNPresent(custUN)) {
      for (int i = 0; i < cust.customers.size(); i++) {
        if (custUN == cust.customers[i].getUserName()) {
          tempCust = &cust.customers[i];
          play = false;
        } else {
          continue;
        }
      }
      prod.printProducts(prod);
      while (notDone) {
        cout << "Enter the productId you'd like to purchase: ";
        cin >> prodId;
        tempProd
      }
      completePurchase(cust, tempProd);
    } else {
      cout << "The Username does not exist! Enter again." << endl;
      play = true;
    }
  }
}

// string transactionID;
// string userID;
// vector<string> productIDs;
// float totalAmount;
// int rewardPoints;
// vector<transaction> transactions;
void transaction::completePurchase(customer &cust, vector<product> tempProds) {
  transaction trans;
  trans.setUserID(cust.getCustID());
  for (int i = 0; i < tempProds.size(); i++) {
    trans.transactions.push_back(tempProds[i]);
  }
}
