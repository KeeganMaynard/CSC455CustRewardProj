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
using namespace std;

int custCount = 1;

class customer
{
public:
    customer();

    string username;
    string fname;
    string lname;
    string dob;
    string ccNum;
    string custID;
    string rewardPoints;
    int customNum;
};

void registerUser()
{
    customer newCustomer;

    newCustomer.username = inputUsername();
    newCustomer.fname = inputFirstName();
    newCustomer.lname = inputLastName();
    newCustomer.dob = inputDOB();
    newCustomer.ccNum = inputCreditCard();
    newCustomer.rewardPoints = inputPoints();
    newCustomer.custID = assignId();
    logNewUser(newCustomer);
}

void removeUser()
{
    string delCustomer;
    cout << "Enter the customer ID that you wish to remove: ";
    cin >> delCustomer;
}

void lookUpUser()
{
}

string inputUsername()
{
    string username = "";
    cout << "Enter your username: ";
    cin >> username;
    if (validateUserName(username))
    {
        return username;
    }
    else
    {
        // call inputUsername again to
        if (isUnique(username))
        {
            cout << "The username must be 8 characters followed by at most 3 numbers" << endl;
        }
        else
        {
            cout << "This username already exists" << endl;
        }
        inputUsername();
    }
}

string inputFirstName()
{
    string firstname = "";
    cout << "Enter your first name: ";
    cin >> firstname;
    if (validateName(firstname))
    {
        return firstname;
    }
    else
    {
        cout << "The name cannot be longer than 15 characters" << endl;
        cout << "The name cannot contain any numbers or special characters" << endl;
        inputFirstName();
    }
}

string inputLastName()
{
    string lastname = "";
    cout << "Enter your last name: ";
    cin >> lastname;
    if (validateName(lastname))
    {
        return lastname;
    }
    else
    {
        cout << "The name cannot be longer than 15 characters" << endl;
        cout << "The name cannot contain any numbers or special characters" << endl;
        inputLastName();
    }
}

string inputDOB()
{
    string dob;
    cout << "Enter your date of birth (MM-DD-YYYY): ";
    cin >> dob;
    if (validateDOB(dob))
    {
        return dob;
    }
    else
    {
        cout << "The date of birth must follow the MM-DD-YYYY format" << endl;
        cout << "MM, DD, and YYYY must be numbers" << endl;
        inputDOB();
    }
}

string inputCreditCard()
{
    string cc;
    cout << "Enter your credit card number: ";
    cin >> cc;
    if (validateCreditCard(cc))
    {
        return cc;
    }
    else
    {
        if (isUnique(cc))
        {
            cout << "The credit card number must follow the xxxx-xxxx-xxxx format" << endl;
            cout << "The credit card number values must be numbers" << endl;
        }
        else
        {
            cout << "This credit card number already exists" << endl;
        }
        inputCreditCard();
    }
}

string inputPoints()
{
    string points;
    cout << "Enter your current reward points: ";
    cin >> points;
    if (validatePoints(points))
    {
        assignId();
    }
    else
    {
        cout << "The reward points must be a positive number" << endl;
        inputPoints();
    }
}

string assignId()
{
    // assign the user an ID - only after their inputs have been
    string newID = "CID";
    // attach 10 digits to end of newID
}

void logNewUser(customer logCustomer)
{
    // log the new user into customers.txt
    ofstream customersLog("customers.txt");
    customersLog << "customer " << custCount << " ID " << logCustomer.custID << endl;
    customersLog << "customer " << custCount << " user name " << logCustomer.username << endl;
    customersLog << "customer " << custCount << " first name " << logCustomer.fname << endl;
    customersLog << "customer " << custCount << " last name " << logCustomer.lname << endl;
    customersLog << "customer " << custCount << " date of birth " << logCustomer.dob << endl;
    customersLog << "customer " << custCount << " credit card number " << logCustomer.ccNum << endl;
    customersLog << "customer " << custCount << " total reward points " << logCustomer.rewardPoints << endl;
    custCount += custCount;
}

bool isUnique(string newValue)
{
    return true;
}

bool validateUserName(string newUserName)
{
    return true;
}

bool validateName(string newName)
{
    return true;
}

bool validateDOB(string newDob)
{
    return true;
}

bool validateCreditCard(string newCreditCard)
{
    return true;
}

bool validatePoints(string newPoints)
{
    return true;
}

#endif