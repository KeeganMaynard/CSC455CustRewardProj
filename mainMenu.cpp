/* Main menu class - the main class of our program
  utilizes: customerRegistration.h, productManagement.h, rewardManagement.h, and
  transaction.h
*/
#include <iostream>
#include <string>

#include "customerRegistration.h"
#include "productManagement.h"
#include "rewardManagement.h"
#include "transaction.h"
using namespace std;

// displayOpts prototype and class object declarations
void displayOpts();
customer cust;
product prod;
transaction trans;
rewards rew;

/* int main() - the driver of our program, gathers user input and performs an
option based on input. Parameters - none Return value - 0, signifies successful
run of the program.
*/
int main() {
  cust.initilize();
  bool run = true;
  while (run) {
    string option = "";
    displayOpts();
    getline(cin, option);

    // switch-case based on user input
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
        rew.redeemRewards();
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

/* void displayOpts() - the purpose of this function is to display the program
options to the user. Parameters - none Return value - none
*/
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
