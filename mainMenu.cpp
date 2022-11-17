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

#include "customerRegistration.h"
#include "productManagement.h"
#include "rewardManagement.h"
#include "transaction.h"
using namespace std;

void displayOpts();
customer cust;
product prod;
transaction trans;
rewards rew;
int main() {
  cust.initilize();
  bool run = true;
  while (run) {
    string option = "";
    displayOpts();
    getline(cin, option);

    switch (stoi(option)) {
      case 1:
        cust.registerUser();
        break;
      case 2:
        cust.removeCustomer();
        break;
      case 3:
        prod.addProduct();
        break;
      case 4:
        prod.removeProduct();
        break;
      case 5:
        trans.shopping(cust, prod);
        break;
      case 6:
        cust.searchCustomer();
        break;
      case 7:
        redeemRewards(rew.rews);
        break;
      case 8:
        cust.shutdown();
        run = false;
        break;
      default:
        cout << "Error. Invalid option entered. Please try again" << endl;
        break;
    }
  }

  return 0;
}

void displayOpts() {
  cout << "Select the number associated with the opperation you wish to perform"
       << endl;
  cout << "[1] Customer registration" << endl;
  cout << "[2] Customer removal" << endl;
  cout << "[3] Product addition" << endl;
  cout << "[4] Product removal" << endl;
  cout << "[5] Shopping" << endl;
  cout << "[6] View customer using customer username" << endl;
  cout << "[7] Redeem rewards" << endl;
  cout << "[8] End session" << endl;
}
