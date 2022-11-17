/*Customer registration class
    author - Keegan Maynard
 */
#ifndef CUSTOMERREGISTRATION_H
#define CUSTOMERREGISTRATION_H
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

class customer {
 private:
  string custID;
  string username;
  string fname;
  string lname;
  string custDOB;
  string custCC;
  int custPoints;

 public:
  customer(){};

  // vector and associated functions to store previously entered and new
  // customers
  vector<customer> customers;
  bool custIdPresent(string);
  bool custCCNPresent(string);
  bool custUNPresent(string);

  // User function
  void registerUser();
  void searchCustomer();
  void removeCustomer();
  string generateID();
  string inputUsername();
  string inputFName();
  string inputLName();
  string inputDOB();
  string inputCCN();
  int inputPoints();

  // utility functions
  void initilize();
  void shutdown();
  void parseData(string);
  void logNewUser(int);
  bool matchCCRegex(string);
  string attachNums(int);
  int retrievePoints(string);
  void setPoints(string, int);
  void displayCustData(int);

  // setter functions
  void setCustID(string newID) { custID = newID; }
  void setUserName(string newUser) { username = newUser; }
  void setFName(string newFirst) { fname = newFirst; }
  void setLName(string newLast) { lname = newLast; }
  void setDOB(string newDOB) { custDOB = newDOB; }
  void setCC(string newCCN) { custCC = newCCN; }
  void setPoints(int newPoints) { custPoints = newPoints; }

  // getter functions
  string getCustID() { return custID; }
  string getUserName() { return username; }
  string getFName() { return fname; }
  string getLName() { return lname; }
  string getDOB() { return custDOB; }
  string getCCN() { return custCC; }
  int getPoints() { return custPoints; }
};

void customer::registerUser() {
  // create a new instance of the customer class
  customer newCustomer;

  newCustomer.setCustID(generateID());
  newCustomer.setUserName(inputUsername());
  newCustomer.setFName(inputFName());
  newCustomer.setLName(inputLName());
  newCustomer.setDOB(inputDOB());
  newCustomer.setCC(inputCCN());
  newCustomer.setPoints(inputPoints());

  // add the new customer to the vector of customers
  customers.push_back(newCustomer);

  // log the most recent index of the vector
  logNewUser(customers.size() - 1);

  cout << "\nCustomer successfully entered\n\n";
}

void customer::searchCustomer() {
  string lookUp;
  cout << "Enter the username for the customer you wish to search: ";
  getline(cin, lookUp);

  if (custUNPresent(lookUp)) {
    // display customer data
    for (int i = 0; i < customers.size(); i++) {
      string &storedUNs = customers[i].username;
      if (storedUNs.compare(lookUp) == 0) {
        displayCustData(i);
      } else { /*No need to catch else statement*/
      }
    }
  } else {
    cout << "That username is not associated with an account" << endl;
  }
}

void customer::removeCustomer() {
  string findCust;
  cout << "Enter the username for the customer you wish to remove: ";
  getline(cin, findCust);

  if (custUNPresent(findCust)) {
    // remove the customer from the vector
    for (int i = 0; i < customers.size(); i++) {
      string &storedUNs = customers[i].username;
      if (storedUNs.compare(findCust) == 0) {
        customers.erase(customers.begin() + i);
      } else {
        /*No need to catch else statement*/
      }
    }
  } else {
    cout << "That username is not associated with an account" << endl;
  }
}

// Function to read the file and fill up the vector
void customer::initilize() {
  ifstream customersLog;
  customersLog.open("customers.txt");

  if (customersLog.is_open()) {
    string line;
    string temp;
    string buffer;
    while (getline(customersLog, line)) {
      // parse data gathered from line
      if (!line.empty())  // Break on empty line
      {
        temp = line.substr(line.find_last_of(' ') + 1, line.length());
        buffer = buffer + temp + " ";
      } else {
        parseData(buffer);
        temp = "";
        buffer = "";
      }
    }
    customersLog.close();
  } else {
    cout << "Error reading customers log file. Please ensure the file is "
            "attached to store customer information."
         << endl;
  }
}

void customer::parseData(string line) {
  string loadID, loadUN, loadFirst, loadLast, loadDOB, loadCC, loadPoints;
  customer loadCust;
  loadID = line.substr(0, line.find_first_of(' '));
  loadCust.setCustID(loadID);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadUN = line.substr(0, line.find_first_of(' '));
  loadCust.setUserName(loadUN);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadFirst = line.substr(0, line.find_first_of(' '));
  loadCust.setFName(loadFirst);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadLast = line.substr(0, line.find_first_of(' '));
  loadCust.setLName(loadLast);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadDOB = line.substr(0, line.find_first_of(' '));
  loadCust.setDOB(loadDOB);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadCC = line.substr(0, line.find_first_of(' '));
  loadCust.setCC(loadCC);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadPoints = line.substr(0, line.find_first_of(' ') - 1);
  loadCust.setPoints(stoi(loadPoints));

  customers.push_back(loadCust);
}

void customer::shutdown() {
  // clear the text file to avoid duplicates
  ofstream logFile("customers.txt");
  logFile.close();

  // write all customers remaining in vector
  for (int i = 0; i < customers.size(); i++) {
    logNewUser(i);
  }
}

string customer::generateID() {
  string newID = "CID";
  int currCount = customers.size() + 1;
  // attach 10 digits at the end
  newID.append(attachNums(currCount));

  if (!custIdPresent(newID)) {
    return newID;
  } else {
    return generateID();
  }
}

string customer::inputUsername() {
  string newUserName = "";
  cout << "Enter your username: ";
  getline(cin, newUserName);
  if (!custUNPresent(newUserName)) {
    // check regex
    if (regex_match(newUserName, regex("^[a-zA-Z]{8,20}[0-9]{0,3}"))) {
      return newUserName;
    } else {
      cout << "The username must be at least 8 characters followed by at most "
              "3 digits"
           << endl;
      return inputUsername();
    }
  } else {
    cout << "This username is already associated with an account" << endl;
    return inputUsername();
  }
}

string customer::inputFName() {
  string newFName = "";
  cout << "Enter your first name: ";
  getline(cin, newFName);
  if (newFName.length() <= 15 && regex_match(newFName, regex("^[A-Za-z]+$"))) {
    return newFName;
  } else {
    cout << "The name must be less than 15 characters and cannot contain "
            "numbers or special characters"
         << endl;
    return inputFName();
  }
}

string customer::inputLName() {
  string newLName = "";
  cout << "Enter your last name: ";
  getline(cin, newLName);
  if (newLName.length() <= 15 && regex_match(newLName, regex("^[A-Za-z]+$"))) {
    return newLName;
  } else {
    cout << "The name must be less than 15 characters and cannot contain "
            "numbers or special characters"
         << endl;
    return inputLName();
  }
}

string customer::inputDOB() {
  string newDOB = "";
  cout << "Enter your date of birth: ";
  getline(cin, newDOB);
  if (regex_match(
          newDOB,
          regex("^(1[0-2]|0[1-9])-(3[01]|[12][0-9]|0[1-9])-[0-9]{4}$"))) {
    return newDOB;
  } else {
    cout << "The date of birth must be entered in the MM-DD-YYYY format"
         << endl;
    return inputDOB();
  }
}

string customer::inputCCN() {
  string newCCN = "";
  cout << "Enter your credit card number: ";
  getline(cin, newCCN);
  if (matchCCRegex(newCCN)) {
    if (!custCCNPresent(newCCN)) {
      return newCCN;
    } else {
      cout << "This credit card number is already associated with an account"
           << endl;
      return inputCCN();
    }
  } else {
    cout << "The credit card number must follow the xxxx-xxxx-xxxx format"
         << endl;
    return inputCCN();
  }
}

int customer::inputPoints() {
  string newPoints = "";
  cout << "Enter your current rewards points: ";
  getline(cin, newPoints);
  int convert = stoi(newPoints);
  if (convert > 0) {
    return convert;
  } else {
    cout << "The current rewards points must be greater than 0" << endl;
    return inputPoints();
  }
}

// append the last customer in the vector to the txt file
void customer::logNewUser(int custNum) {
  string &custID = customers[custNum].custID;
  string &username = customers[custNum].username;
  string &fname = customers[custNum].fname;
  string &lname = customers[custNum].lname;
  string &dob = customers[custNum].custDOB;
  string &CCNum = customers[custNum].custCC;
  int &points = customers[custNum].custPoints;

  // open the log file and set to append data
  ofstream customersLog;
  customersLog.open("customers.txt", ios::app);

  // log the new user into customers.txt
  customersLog << "customer " << custNum << " ID " << custID << endl;
  customersLog << "customer " << custNum << " user name " << username << endl;
  customersLog << "customer " << custNum << " first name " << fname << endl;
  customersLog << "customer " << custNum << " last name " << lname << endl;
  customersLog << "customer " << custNum << " date of birth " << dob << endl;
  customersLog << "customer " << custNum << " credit card number " << CCNum
               << endl;
  customersLog << "customer " << custNum << " total reward points " << points
               << "\n\n";

  // close the log file
  customersLog.close();
}

bool customer::custIdPresent(string value) {
  for (int i = 0; i < customers.size(); i++) {
    string &custIDs = customers[i].custID;
    if (custIDs.compare(value) == 0) {
      return true;
    } else {
      /*No need to catch else statement*/
    }
  }

  return false;
}

bool customer::custCCNPresent(string value) {
  for (int i = 0; i < customers.size(); i++) {
    string &custCCNs = customers[i].custCC;
    if (custCCNs.compare(value) == 0) {
      return true;
    } else {
      /*No need to catch else statement*/
    }
  }

  return false;
}

bool customer::custUNPresent(string value) {
  for (int i = 0; i < customers.size(); i++) {
    string &custUNs = customers[i].username;
    if (custUNs.compare(value) == 0) {
      return true;
    } else {
      /*No need to catch else statement*/
    }
  }

  return false;
}

bool customer::matchCCRegex(string value) {
  // match all kinds of credit cards from various companies
  string validation = "^\\d{4}[-, ]?\\d{4}[-, ]?\\d{4}$";

  if (regex_match(value, regex(validation))) {
    return true;
  } else {
    return false;
  }
}

string customer::attachNums(int count) {
  string convert = to_string(count);
  string padding;

  switch (convert.length()) {
    case 1:
      padding = "000000000" + convert;
      break;
    case 2:
      padding = "00000000" + convert;
      break;
    case 3:
      padding = "0000000" + convert;
      break;
    case 4:
      padding = "000000" + convert;
      break;
    default:
      padding = convert;
      break;
  }

  return padding;
}

int customer::retrievePoints(string lookupID) {
  for (int i = 0; i < customers.size(); i++) {
    string &custUN = customers[i].username;
    if (custUN.compare(lookupID) == 0) {
      int &custPoints = customers[i].custPoints;
      return custPoints;
    } else {
      /*No need to catch else statement*/
    }
  }

  return 0;
}

void customer::setPoints(string lookupID, int newPoints) {
  for (int i = 0; i < customers.size(); i++) {
    string &custUN = customers[i].username;
    if (custUN.compare(lookupID) == 0) {
      customers[i].custPoints = newPoints;
    }
  }
}

void customer::displayCustData(int custNum) {
  string &custID = customers[custNum].custID;
  string &username = customers[custNum].username;
  string &fname = customers[custNum].fname;
  string &lname = customers[custNum].lname;
  string &dob = customers[custNum].custDOB;
  string &CCNum = customers[custNum].custCC;
  int &points = customers[custNum].custPoints;

  cout << "customer " << custNum << " ID " << custID << endl;
  cout << "customer " << custNum << " User Name " << username << endl;
  cout << "customer " << custNum << " First Name " << fname << endl;
  cout << "customer " << custNum << " Last Name " << lname << endl;
  cout << "customer " << custNum << " Date of Birth " << dob << endl;
  cout << "customer " << custNum << " Credit Card " << CCNum << endl;
  cout << "customer " << custNum << " Points " << points << endl;
}
#endif