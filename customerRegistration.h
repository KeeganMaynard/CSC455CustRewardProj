/*Customer registration class
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

public:
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
    void parseData(string);
    void logNewUser(int);
    bool matchCCRegex(string);
    string attachNums(int);
    int retrievePoints(string);
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

void customer::registerUser()
{
    // create a new instance of the customer class
    customer newCustomer;

    newCustomer.setCustID(generateID());
    newCustomer.setUserName(inputUsername());
    newCustomer.setFName(inputFName());
    newCustomer.setLName(inputLName());
    newCustomer.setDOB(inputDOB());
    newCustomer.setCC(inputCCN());
    newCustomer.setPoints(inputPoints());

    // add the new customer to the list of customers
    customers.push_back(newCustomer);
    logNewUser(customers.size());
}

void customer::searchCustomer()
{
    string lookUp;
    cout << "Enter the customer ID for the customer you wish to search: ";
    getline(cin, lookUp);

    if (custIdPresent(lookUp))
    {
        // display customer data
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].custID.compare(lookUp))
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
        cout << "That user ID is not associated with an account" << endl;
    }
}

void customer::removeCustomer()
{
    string findCust;
    cout << "Enter the customer ID for the customer you wish to remove: ";
    getline(cin, findCust);

    if (custIdPresent(findCust))
    {
        // remove the customer from the vector
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].custID.compare(findCust))
            {
                customers.erase(customers.begin() + i);
            }
            else
            {
                /*No need to catch else statement*/
            }
        }
    }
    else
    {
        cout << "That user ID is not associated with an account" << endl;
    }
}

// Function to read the file and fill up the vector
void customer::initilize()
{
    ifstream customersLog;
    customersLog.open("customers.txt");

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
                temp = line.substr(line.find_last_of(' ') + 1, line.length());
                buffer = buffer + temp + " ";
            }
            else
            {
                parseData(buffer);
            }
        }
        customersLog.close();
    }
    else
    {
        cout << "Error reading customers log file. Please ensure the file is attached to store customer information." << endl;
    }
}

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

    customers.push_back(loadCust);
}

string customer::generateID()
{
    string newID = "CID";
    int currCount = customers.size() + 1;
    // attach 10 digits at the end
    newID.append(attachNums(currCount));

    if (!custIdPresent(newID))
    {
        return newID;
    }
    else
    {
        return "There are no valid IDs available";
    }
}

string customer::inputUsername()
{
    string newUserName = "";
    cout << "Enter your username: ";
    getline(cin, newUserName);
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
            inputUsername();
        }
    }
    else
    {
        cout << "This username is already associated with an account" << endl;
        inputUsername();
    }
}

string customer::inputFName()
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

string customer::inputLName()
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

string customer::inputDOB()
{
    string newDOB = "";
    cout << "Enter your date of birth: ";
    getline(cin, newDOB);
    if (regex_match(newDOB, regex("^(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}$")))
    {
        return newDOB;
    }
    else
    {
        cout << "The date of birth must be entered in the MM-DD-YYYY format" << endl;
        inputDOB();
    }
}

string customer::inputCCN()
{
    string newCCN = "";
    cout << "Enter your credit card number: ";
    getline(cin, newCCN);
    if (matchCCRegex(newCCN))
    {
        if (!custCCNPresent(newCCN))
        {
            return newCCN;
        }
        else
        {
            cout << "This credit card number is already associated with an account" << endl;
            inputCCN();
        }
    }
    else
    {
        cout << "The credit card number must follow the xxxx-xxxx-xxxx format" << endl;
        inputCCN();
    }
}

int customer::inputPoints()
{
    string newPoints = "";
    cout << "Enter your current rewards points: ";
    getline(cin, newPoints);
    int convert = stoi(newPoints);
    if (convert > 0)
    {
        return convert;
    }
    else
    {
        cout << "The current rewards points must be greater than 0" << endl;
        inputPoints();
    }
}

// append the last customer in the vector to the txt file
void customer::logNewUser(int custNum)
{
    // open the log file and set to append data
    ofstream customersLog;
    customersLog.open("customers.txt", ios::app);

    // log the new user into customers.txt
    customersLog << "customer " << customers.size() << " ID " << customers[custNum].custID << endl;
    customersLog << "customer " << customers.size() << " user name " << customers[custNum].username << endl;
    customersLog << "customer " << customers.size() << " first name " << customers[custNum].fname << endl;
    customersLog << "customer " << customers.size() << " last name " << customers[custNum].lname << endl;
    customersLog << "customer " << customers.size() << " date of birth " << customers[custNum].custDOB << endl;
    customersLog << "customer " << customers.size() << " credit card number " << customers[custNum].custCC << endl;
    customersLog << "customer " << customers.size() << " total reward points " << customers[custNum].custPoints << "\n\n";

    // close the log file
    customersLog.close();
}

bool customer::custIdPresent(string value)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].custID.compare(value))
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

bool customer::custCCNPresent(string value)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].custCC.compare(value))
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

bool customer::custUNPresent(string value)
{
    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].username.compare(value))
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

bool customer::matchCCRegex(string value)
{
    // match all kinds of credit cards from various companies
    string validation = "^(?:4[0-9]{12}(?:[0-9]{3})? |  (?:5[1-5][0-9]{2} | 222[1-9]|22[3-9][0-9]|2[3-6][0-9]{2}|27[01][0-9]|2720)[0-9]{12} ";
    string validation2 = " |  3[47][0-9]{13} |  3(?:0[0-5]|[68][0-9])[0-9]{11} |  6(?:011|5[0-9]{2})[0-9]{12} |  (?:2131|1800|35\d{3})\d{11})$";
    validation.append(validation2);

    if (regex_match(value, regex(validation)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string customer::attachNums(int count)
{
    string convert = to_string(count);
    string padding;

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

int customer::retrievePoints(string lookupID)
{

    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].custID.compare(lookupID))
        {
            return customers[i].custPoints;
        }
        else
        {
            /*No need to catch else statement*/
        }
    }

    return 0;
}

void customer::displayCustData(int custNum)
{
    cout << "customer " << custNum << " " << customers[custNum].custID << endl;
    cout << "customer " << custNum << " " << customers[custNum].username << endl;
    cout << "customer " << custNum << " " << customers[custNum].fname << endl;
    cout << "customer " << custNum << " " << customers[custNum].lname << endl;
    cout << "customer " << custNum << " " << customers[custNum].custDOB << endl;
    cout << "customer " << custNum << " " << customers[custNum].custCC << endl;
    cout << "customer " << custNum << " " << customers[custNum].custPoints << endl;
}
#endif