/*Transaction class - will connect with mainMenu.cpp
    used to house transaction data and will write to "transaction.txt"
*/

#define TransactionManager_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class transaction {
 private:
  string transactionID;
  string userID;
  vector<string> productIDs;
  float totalAmount;
  int rewardPoints;

 public:
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
};

/*
  This function handles reading from and writing to files for the transaction
  system Parameters: boolean option: option to read or write files, 1 being read
  0 being write string file: the file to be read or wrote too vecto

  */
vector<transaction> readWriteFiles(bool option, string file,
                                   vector<transaction> transactions) {
  fstream myFile;

  // reading
  if (option == 1) {
    vector<transaction> transactionList;
    myFile.open(file);
  }
  // writing
  else if (option == 0) {
  }
}

vector<string> readFile(string file) {
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

vector<string> processProductIDs(string line) {
  string s;
  string tmp;
  stringstream ss(s);
  vector<string> pIDs;
  while (getline(ss, tmp, ',')) {
    pIDs.push_back(tmp);
  }
  return pIDs;
}

vector<transaction> createTransactions(vector<string> lines) {
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