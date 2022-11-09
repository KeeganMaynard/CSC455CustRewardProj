/*Customer registration class - will connect with mainMenu.cpp
    user must register to benefit from the reward service
    - user name:
        - consists of at least 8 characters, followed by at most 3 numbers
            - ex: uniqueUser123
            - do we need to prevent special characters?
        - must be unique (cannot already exist)
    - first name:
        - must be a string no longer than 15 characters
        - does not contain any numbers or special characters
    - last name:
        - same as first name
    - date of birth:
        - Must be in MM-DD-YYYY format
            ex: 01-23-2022
        - values must be ints
        - how do we validate? Do we need to check if MM <= 12, DD <=30, YYYY <=2022?
    - credit card number:
        - must be unique (cannot already exist)
        - must follow format xxxx-xxx-xxxx (4-3-4)
            ex: 1234-567-8910
        - must be ints
    - system will assign unique user ID:
        - must be unique (cannot already exist)
        - must start with "CID", follow by 10 digits
            ex: CID1234567890
        - only assign user ID AFTER user input has been validated!!
    - reward points:
        - must be a positive number
        - are we assigning 0 or allowing user to enter points already earned?
    - all user information must be saved in a file named "customers.txt"
        - check assignment.pdf for format
        - only write to file AFTER user input has been validated!!
    - will need to split all inputs into their own functions
        - make logging its own function
        - make validation its own function(s)
    - will need to be able to read PREVIOUS RECORDS
*/
#ifndef CUSTOMERREGISTRATION_H
#define CUSTOMERREGISTRATION_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

class customer
{
private:
    string custID;
    string username;
    string fname;
    string lname;
    string custDOB;
    string custCC;
    int custPoints;
    int custCount;

public:
    customer(){};

    // vectors to store previously entered values - to make sure they are unique
    vector<string> previousIDs;
    vector<string> previousUN;
    vector<string> previousCCN;

    // setter functions
    void setCustID(string newID) { custID = newID; }
    void setUserName(string newUser) { username = newUser; }
    void setFName(string newFirst) { fname = newFirst; }
    void setLName(string newLast) { lname = newLast; }
    void setDOB(string newDOB) { custDOB = newDOB; }
    void setCC(string newCCN) { custCC = newCCN; }
    void setPoints(int newPoints) { custPoints = newPoints; }
    void setCount(int newCount) { custCount = newCount; }

    // getter functions
    string getCustID() { return custID; }
    string getUserName() { return username; }
    string getFName() { return fname; }
    string getLName() { return lname; }
    string getDOB() { return custDOB; }
    string getCCN() { return custCC; }
    int getPoints() { return custPoints; }
    int getCount() { return custCount; }
};

void registerUser()
{
    customer newCustomer;

    newCustomer.setCustID(generateID());
    newCustomer.setUserName(inputUsername());
    newCustomer.setFName(inputFName());
    newCustomer.setLName(inputLName());
    newCustomer.setDOB(inputDOB());
    newCustomer.setCC(inputCCN());
    newCustomer.setPoints(inputPoints());
    newCustomer.setCount(incCount());
    logNewUser(newCustomer);
}

void searchCustomer()
{
    string lookUp;
    cout << "Enter the customer ID for the customer you wish to search: ";
    getline(cin, lookUp);
}

void removeCustomer()
{
    string findCust;
    cout << "Enter the customer ID for the customer you wish to remove: ";
    getline(cin, findCust);
}

string generateID()
{
    string newID = "CID";
    // attach 10 digits at the end
    return newID;
}

string inputUsername()
{
    string newUserName = "";
    cout << "Enter your username: ";
    getline(cin, newUserName);
    return newUserName;
}

string inputFName()
{
    string newFName = "";
    cout << "Enter your first name: ";
    getline(cin, newFName);
    if (newFName.length() <= 15 && regex_match(newFName, regex("^[A-Za-z]+$")))
    {
        return newFName;
    }
    else
    {
        cout << "The name must be less than 15 characters and cannot contain numbers or special characters" << endl;
        inputFName();
    }
}

string inputLName()
{
    string newLName = "";
    cout << "Enter your last name: ";
    getline(cin, newLName);
    if (newLName.length() <= 15 && regex_match(newLName, regex("^[A-Za-z]+$")))
    {
        return newLName;
    }
    else
    {
        cout << "The name must be less than 15 characters and cannot contain numbers or special characters" << endl;
        inputLName();
    }
}

string inputDOB()
{
    string newDOB = "";
    cout << "Enter your date of birth: ";
    getline(cin, newDOB);
    return newDOB;
}

string inputCCN()
{
    string newCCN = "";
    cout << "Enter your credit card number: ";
    getline(cin, newCCN);
    return newCCN;
}

int inputPoints()
{
    string newPoints = "";
    cout << "Enter your current rewards points: ";
    getline(cin, newPoints);
    int convert = stoi(newPoints);
    return convert;
}

int incCount()
{

    return 0;
}

// pass the instance of customer to the log function
void logNewUser(customer &newCust)
{
    // log the new user into customers.txt
    ofstream customersLog("customers.txt");
    customersLog << "customer " << newCust.getCount() << " ID " << newCust.getCustID() << endl;
    customersLog << "customer " << newCust.getCount() << " user name " << newCust.getUserName() << endl;
    customersLog << "customer " << newCust.getCount() << " first name " << newCust.getFName() << endl;
    customersLog << "customer " << newCust.getCount() << " last name " << newCust.getLName() << endl;
    customersLog << "customer " << newCust.getCount() << " date of birth " << newCust.getDOB() << endl;
    customersLog << "customer " << newCust.getCount() << " credit card number " << newCust.getCCN() << endl;
    customersLog << "customer " << newCust.getCount() << " total reward points " << newCust.getPoints() << "\n\n";
    customersLog.close();
}
#endif