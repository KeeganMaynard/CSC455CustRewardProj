/*Customer registration class - contains the implementation for all customer functions
    author - Keegan Maynard
*/
#ifndef CUSTOMERREGISTRATION_H
#define CUSTOMERREGISTRATION_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

// customer class - utilized to store and represent customer information
class customer
{
private:
  // customer attributes
  string custID;
  string username;
  string fname;
  string lname;
  string custDOB;
  string custCC;
  int custPoints;

public:
  // default constructor
  customer(){};

  // vector and associated functions to store previously entered and new customers
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

/* void registerUser() - a method of the customer class, this function is utilized to create a new instance
of the customer class, gather attribute values for this instance, append the instance to the vector of
customers, and, finally, log the new user to the text file.
Parameters - none
Return value - none
*/
void customer::registerUser()
{
  // create a new instance of the customer class
  customer newCustomer;

  // gather newCustomer attributes
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

/* void searchCustomer() - a method of the customer class, this function is utilized to find and display
customer data based on a user-input username.
Parameters - none
Return value - none
*/
void customer::searchCustomer()
{
  string lookUp;
  cout << "Enter the username for the customer you wish to search: ";
  getline(cin, lookUp);

  // test if entered username actually exists
  if (custUNPresent(lookUp))
  {
    // display customer data
    for (int i = 0; i < customers.size(); i++)
    {
      string &storedUNs = customers[i].username;
      if (storedUNs.compare(lookUp) == 0)
      {
        displayCustData(i);
      }
      else
      { /*No need to catch else statement*/
      }
    }
  }
  else
  {
    cout << "That username is not associated with an account" << endl;
  }
}

/* void removeCustomer() - a method of the customer class, this function is utilized to find and remove a
customer based on a user-input username.
Parameters - none
Return value - none
*/
void customer::removeCustomer()
{
  string findCust;
  cout << "Enter the username for the customer you wish to remove: ";
  getline(cin, findCust);

  // test if entered username actually exists
  if (custUNPresent(findCust))
  {
    // remove the customer from the vector
    for (int i = 0; i < customers.size(); i++)
    {
      string &storedUNs = customers[i].username;
      if (storedUNs.compare(findCust) == 0)
      {
        customers.erase(customers.begin() + i);
        cout << "\nCustomer removed successfully\n\n";
      }
      else
      {
        /*No need to catch else statement*/
      }
    }
  }
  else
  {
    cout << "That username is not associated with an account" << endl;
  }
}

/* void initilize() - a method of the customer class, this function is utilized to read the customer log
file, customers.txt, parse the lines, and send the data to parseData().
Parameters - none
Return value - none
*/
void customer::initilize()
{
  // open the log file - customers.txt
  ifstream customersLog;
  customersLog.open("customers.txt");

  // test file access
  if (customersLog.is_open())
  {
    string line;
    string temp;
    string buffer;
    while (getline(customersLog, line))
    {
      // parse data gathered from line
      if (!line.empty()) // Break on empty line
      {
        // find the last space in line, store the last word in buffer
        temp = line.substr(line.find_last_of(' ') + 1, line.length());
        buffer = buffer + temp + " ";
      }
      else
      {
        // send the buffer to parseData() and clear temp and buffer
        parseData(buffer);
        temp = "";
        buffer = "";
      }
    }
    // close the log file
    customersLog.close();
  }
  else
  {
    cout << "Error reading customers log file. Please ensure the file is attached to store customer information." << endl;
  }
}

/* void parseData(string) - a method of the customer class, this function is utilized to parse a string of
customer attributes, assign them to an instance of the customer class, and append the instance to the vector
of customers.
Parameters - string line, a string representation of customer attributes gathered from the log file
Return values - none
*/
void customer::parseData(string line)
{
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

  // append the customer to the vector of customers
  customers.push_back(loadCust);
}

/* void shutdown() - a method of the customer class, this function is utilized at program termination, it
clears the log file of all customer data, then writes all customers in the current vector. This function
ensures removed customers do not remain in the log
Parameters - none
Return value - none
*/
void customer::shutdown()
{
  // clear the text file to avoid duplicates
  ofstream logFile("customers.txt");
  logFile.close();

  // write all customers remaining in vector
  for (int i = 0; i < customers.size(); i++)
  {
    logNewUser(i);
  }
}

/* string generateID() - a recursive method of the customer class, this function is utilized to create the
unique customer ID for all customers.
Parameters - none
Return value - string, the customer ID that will be associated with an account
*/
string customer::generateID()
{
  string newID = "CID";
  int currCount = customers.size() + 1;
  // attach 10 digits at the end
  newID.append(attachNums(currCount));

  // test newID is unique
  if (!custIdPresent(newID))
  {
    return newID;
  }
  else
  {
    return generateID();
  }
}

/* string inputUsername() - a recursive method of the customer class, this function is utilized to gather
user input for the username, ensure it is unique, and validate it according to system requirements.
Parameters - none
Return value - string, the customer username that will be associated with an account
*/
string customer::inputUsername()
{
  string newUserName = "";
  cout << "Enter your username: ";
  getline(cin, newUserName);

  // test newUserName is unique
  if (!custUNPresent(newUserName))
  {
    // check regex
    if (regex_match(newUserName, regex("^[a-zA-Z]{8,20}[0-9]{0,3}")))
    {
      return newUserName;
    }
    else
    {
      cout << "The username must be at least 8 characters followed by at most 3 digits" << endl;
      // recursive function call if validation failed
      return inputUsername();
    }
  }
  else
  {
    cout << "This username is already associated with an account" << endl;
    // recursive function call if validation failed
    return inputUsername();
  }
}

/* string inputFName() - a recursive method of the customer class, this function is utilized to gather
user input for the first name and validate it according to system requirements.
Parameters - none
Return value - string, the customer first name that will be associated with an account
*/
string customer::inputFName()
{
  string newFName = "";
  cout << "Enter your first name: ";
  getline(cin, newFName);
  // validate the first name input
  if (newFName.length() <= 15 && regex_match(newFName, regex("^[A-Za-z]+$")))
  {
    return newFName;
  }
  else
  {
    cout << "The name must be less than 15 characters and cannot contain numbers or special characters" << endl;
    // recursive function call if validation failed
    return inputFName();
  }
}

/* string inputLName() - a recursive method of the customer class, this function is utilized to gather
user input for the last name and validate it according to system requirements.
Parameters - none
Return value - string, the customer last name that will be associated with an account
*/
string customer::inputLName()
{
  string newLName = "";
  cout << "Enter your last name: ";
  getline(cin, newLName);
  // validate the last name input
  if (newLName.length() <= 15 && regex_match(newLName, regex("^[A-Za-z]+$")))
  {
    return newLName;
  }
  else
  {
    cout << "The name must be less than 15 characters and cannot contain numbers or special characters" << endl;
    // recursive function call if validation failed
    return inputLName();
  }
}

/* string inputDOB() - a recursive method of the customer class, this function is utilized to gather
user input for the date of birth and validate it according to system requirements.
Parameters - none
Return value - string, the customer date of birth that will be associated with an account
*/
string customer::inputDOB()
{
  string newDOB = "";
  cout << "Enter your date of birth: ";
  getline(cin, newDOB);
  // validate the DOB input
  if (regex_match(newDOB, regex("^(1[0-2]|0[1-9])-(3[01]|[12][0-9]|0[1-9])-[0-9]{4}$")))
  {
    return newDOB;
  }
  else
  {
    cout << "The date of birth must be entered in the MM-DD-YYYY format" << endl;
    // recursive function call if vaidation failed
    return inputDOB();
  }
}

/* string inputCCN() - a recursive method of the customer class, this function is utilized to gather user
input for the credit card number, ensure it is unique, and validate it according to system requirements.
Parameters - none
Return value - string, the customer credit card number that will be associated with an account
*/
string customer::inputCCN()
{
  string newCCN = "";
  cout << "Enter your credit card number: ";
  getline(cin, newCCN);
  // validate the CCN input
  if (regex_match(newCCN, regex("^\\d{4}[-, ]?\\d{4}[-, ]?\\d{4}$")))
  {
    // test if CCN is unique
    if (!custCCNPresent(newCCN))
    {
      return newCCN;
    }
    else
    {
      cout << "This credit card number is already associated with an account" << endl;
      // recursive function call if CCN already present
      return inputCCN();
    }
  }
  else
  {
    cout << "The credit card number must follow the xxxx-xxxx-xxxx format" << endl;
    // recursive function call if validation failed
    return inputCCN();
  }
}

/* int inputPoints() - a recursive method of the customer class, this function is utilized to gather user
input for the customer's reward points and validate it according to system requirements.
Parameters - none
Return value - int, the customer reward points that will be associated with an account
*/
int customer::inputPoints()
{
  string newPoints = "";
  cout << "Enter your current rewards points: ";
  getline(cin, newPoints);
  int convert = stoi(newPoints);
  // validate the points input
  if (convert > 0)
  {
    return convert;
  }
  else
  {
    cout << "The current rewards points must be greater than 0" << endl;
    // recursive function call if validation failed
    return inputPoints();
  }
}

/* void logNewUser(int) - a method of the customer class, this function is utilized to append a new customer
to the log file.
Parameters - int custNum, the value of the index in the customers vector to retrieve data from
Return value - none
*/
void customer::logNewUser(int custNum)
{
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
  customersLog << "customer " << custNum << " credit card number " << CCNum << endl;
  customersLog << "customer " << custNum << " total reward points " << points << "\n\n";

  // close the log file
  customersLog.close();
}

/* bool custIdPresent(string) - a method of the customer class, this function is utilized to test if the
value passed to the function is already present in the vector of customers. This function ensures the
customer ID is unique.
Parameters - string value, the customer Id we want to determine if it is already associated with an account
Return values - true or false
  returns true if the passed customer Id is found in the vector
  returns false if the passed customer Id is not found in the vector
*/
bool customer::custIdPresent(string value)
{
  // for each index in the vector
  for (int i = 0; i < customers.size(); i++)
  {
    string &custIDs = customers[i].custID;
    // test if custID equal to value
    if (custIDs.compare(value) == 0)
    {
      return true;
    }
    else
    {
      /*No need to catch else statement*/
    }
  }

  return false;
}

/* bool custCCNPresent(string) - a method of the customer class, this function is utilized to test if the
value passed to the function is already present in the vector of customers. This function ensures the
customer credit card number is unique.
Parameters - string value, the customer credit card number we want to determine if it is already
associated with an account
Return values - true or false
  returns true if the passed customer CCN is found in the vector
  returns false if the passed customer CCN is not found in the vector
*/
bool customer::custCCNPresent(string value)
{
  // for each index in the vector
  for (int i = 0; i < customers.size(); i++)
  {
    string &custCCNs = customers[i].custCC;
    // test if cust CCN equal to value
    if (custCCNs.compare(value) == 0)
    {
      return true;
    }
    else
    {
      /*No need to catch else statement*/
    }
  }

  return false;
}

/* bool custUNPresent(string) - a method of the customer class, this function is utilized to test if the
value passed to the function is already present in the vector of customers. This function ensures the
customer username is unique.
Parameters - string value, the customer username we want to determine if it is already associated with an
account.
Return values - true or false
  returns true if the passed customer username is found in the vector
  returns false if the passed customer username is not found in the vector
*/
bool customer::custUNPresent(string value)
{
  // for each index in the vector
  for (int i = 0; i < customers.size(); i++)
  {
    string &custUNs = customers[i].username;
    // test if cust UN equal to value
    if (custUNs.compare(value) == 0)
    {
      return true;
    }
    else
    {
      /*No need to catch else statement*/
    }
  }

  return false;
}

/* string attachNums(int) - a method of the customer class, this function is utilized to attach the
appropriate amount of 0's to the customer Id based on the length of the customer count converted to a string.
Parameters - int count, the size of the vector passed to be converted to a string to ensure a unique digit
sequence is created for the customer Id.
Return values - string padding, the customer Id that will be associated with an account
*/
string customer::attachNums(int count)
{
  // convert size of vector to string
  string convert = to_string(count);
  string padding;

  // swithc-case based on length of vector size conversion
  switch (convert.length())
  {
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

/* int retrievePoints(string) - a method of the customer class, this function is utilized to gather the
amount of rewards points a customer has.
Parameters - string lookupID, the value of the customer username whose points we want to retrieve
Return value - int custPoints, the value of the points attribute of the instance of customer selected by
the username
*/
int customer::retrievePoints(string lookupID)
{
  // for each index in the vector
  for (int i = 0; i < customers.size(); i++)
  {
    string &custUN = customers[i].username;
    // test if cust UN equal to lookupID
    if (custUN.compare(lookupID) == 0)
    {
      // retrieve that customer's points
      int &custPoints = customers[i].custPoints;
      return custPoints;
    }
    else
    {
      /*No need to catch else statement*/
    }
  }

  return 0;
}

/* void setPoints(string, int) - a method of the customer class, this function is utilized to update a
customer's reward points attribute.
Parameters - string lookupID and int newPoints
  string lookupID - the value of the customer username whose points we want to update
  int newPoints - the new value we want to set the points attribute to
Return value - none
*/
void customer::setPoints(string lookupID, int newPoints)
{
  // for each index in the vector
  for (int i = 0; i < customers.size(); i++)
  {
    string &custUN = customers[i].username;
    // test if cust UN equal to lookupID
    if (custUN.compare(lookupID) == 0)
    {
      // update that customer's points
      customers[i].custPoints = newPoints;
    }
  }
}

/* void displayCustData(int) - a method of the customer class, this function is utilized to retrieve and
display all customer information.
Parameters - int custNum, the value of the index in the vector for the customer data we want to retrieve
Return values - none
*/
void customer::displayCustData(int custNum)
{
  // gather customer data from the index passed to the function
  string &custID = customers[custNum].custID;
  string &username = customers[custNum].username;
  string &fname = customers[custNum].fname;
  string &lname = customers[custNum].lname;
  string &dob = customers[custNum].custDOB;
  string &CCNum = customers[custNum].custCC;
  int &points = customers[custNum].custPoints;

  // display the data
  cout << "customer " << custNum << " ID " << custID << endl;
  cout << "customer " << custNum << " User Name " << username << endl;
  cout << "customer " << custNum << " First Name " << fname << endl;
  cout << "customer " << custNum << " Last Name " << lname << endl;
  cout << "customer " << custNum << " Date of Birth " << dob << endl;
  cout << "customer " << custNum << " Credit Card " << CCNum << endl;
  cout << "customer " << custNum << " Points " << points << endl;
}
#endif