/* Main menu class - the driver of the program
    create a menu system that provides the following options:
    - customer registration (customerRegistration.h)
    - customer removal (customerRegistration.h)
    - product addition (productManagement.h)
    - product removal (productManagement.h)
    - shopping (here or make transaction.h?)
        - if here: all transactions must be saved in a file named
   "transactions.txt"
            - check assignment.pdf for format
    - view customer using customer ID (customerRegistration.h)
    - redeem rewards (rewardManagement.h)
*/
#include <iostream>
#include <string>

#include "transaction.h"
using namespace std;

int main() {
  vector<string> productIDs;
  for (int i = 0; i < 10; i++) {
    productIDs.push_back("t" + to_string(i));
  }
  transaction test1("test", "test", productIDs, 1.4, 10);
  transaction test2("test2", "test2", productIDs, 2.4, 11);
  vector<transaction> transactions = {test1, test2};
  writeTransactions(transactions);
}

void displayOpts() {
  cout << "Select the number associated with the opperation you wish to perform"
       << endl;
  cout << "[1] Customer registration" << endl;
  cout << "[2] Customer removal" << endl;
  cout << "[3] Product addition" << endl;
  cout << "[4] Product removal" << endl;
  cout << "[5] Shopping" << endl;
  cout << "[6] View customer using customer ID" << endl;
  cout << "[7] Redeem rewards" << endl;
  cout << "[8] End session" << endl;
}