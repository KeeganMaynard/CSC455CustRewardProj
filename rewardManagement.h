/*Reward management class - will connect with mainMenu.cpp
    this service allows the manager to specify the following
    - the number of points awarded for a given shopping amount
    - the gifts that can be redeemed given the total number of reward points
    - will need function that determine if redeem points are enough
        - ie. function to check if points cost > customer points
*/
#ifndef REWARDMANAGEMENT_H
#define REWARDMANAGEMENT_H
#include "customerRegistration.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class rewards
{
public:
    string gift;
    int giftValue;
    int moneySpent;
    int pointsEarned;

    rewards(){};
    void setGift(string newGift) { gift = newGift; }
    void setGiftValue(int newGiftValue) { giftValue = newGiftValue; }
    void setMoneySpent(int newMoneySpent) { moneySpent = newMoneySpent; }
    void setPointsEarned(int newPointsEarned) { pointsEarned = newPointsEarned; }

    string getGift() { return gift; }
    int getGiftValue() { return giftValue; }
    int getMoneySpent() { return moneySpent; }
    int getPointsEarned() { return pointsEarned; }
};

// Function prototypes
string inputGift();
int inputGiftValue();
int inputMoneySpent();
int inputPointsEarned();
bool validateGift(string);
bool validateGiftValue(int);
bool validateMoneySpent(int);
bool validatePointsEarned(int);

// Declaration and Assignment of the Variables
void rewardValues()
{
    rewards newRewards;

    newRewards.setGift(inputGift());
    newRewards.setGiftValue(inputGiftValue());
    newRewards.setMoneySpent(inputMoneySpent());
    newRewards.setPointsEarned(inputPointsEarned());
    // logRewards(newRewards);
}

string inputGift()
{
    string gift = "";
    cout << "Enter the available reward gift: ";
    cin >> gift;
    if (validateGift(gift))
    {
        return gift;
    }
    else
    {
        cout << "Gift must be a valid String";
        inputGift();
    }

    // Default return statement - will never be hit
    return "Unable to enter a valid gift name";
}

int inputGiftValue()
{
    int giftValue = 0;
    cout << "Enter the cost of the rewards gift: ";
    cin >> giftValue;
    if (validateGiftValue(giftValue))
    {
        return giftValue;
    }
    else
    {
        cout << "Please enter a positive numerical value.";
        inputGiftValue();
    }

    // Default return statement - will never be hit
    return 100;
}

int inputMoneySpent()
{
    int moneySpent = 0;
    cout << "Enter the total shopping amount: ";
    cin >> moneySpent;
    if (validateMoneySpent(moneySpent))
    {
        return moneySpent;
    }
    else
    {
        cout << "Please enter a positive numerical value.";
        inputMoneySpent();
    }

    // Default return statement - will never be hit
    return 100;
}

int inputPointsEarned()
{
    int pointsEarned = 0;
    cout << "Enter points earned from shopping: ";
    cin >> pointsEarned;
    if (validatePointsEarned(pointsEarned))
    {
        return pointsEarned;
    }
    else
    {
        cout << "Please eter a positive numerical value. ";
    }

    // Default return statement - will never be hit
    return 1;
}

// Writing of the values to the database
/*
void logRewards(rewards &newRewards)
{
    fstream log;
    log.open("rewards.txt", fstream::app);
    if(log.is_open())
    {
        log << "Rewards Gift Item: " << newRewards.getGift() << endl;
        log << "Reward Gift Cost: " << newRewards.getGiftValue() << endl;
        log << "Customer Total Spending: " << newRewards.getMoneySpent() << endl;
        log << "Customer Points Earned: " << newRewards.getPointsEarned() << endl;
    }

}
*/
bool validateGift(string newGift)
{
    return true;
}

bool validateGiftValue(int newGiftValue)
{
    if (isdigit(newGiftValue))
    {
        if (newGiftValue > 0)
        {
            return true;
        }
    }
    else
    {
        return false;
    }

    // Default return statement - will never be hit
    return true;
}

bool validateMoneySpent(int newMoneySpent)
{
    if (isdigit(newMoneySpent))
    {
        if (newMoneySpent > 0)
        {
            return true;
        }
    }
    else
    {
        return false;
    }

    // Default return statement - will never be hit
    return true;
}

bool validatePointsEarned(int newPointsEarned)
{
    if (isdigit(newPointsEarned))
    {
        if (newPointsEarned > 0)
        {
            return true;
        }
    }
    else
    {
        return false;
    }

    // Default return statement - will never be hit
    return true;
}

vector<string> readFromFile(string file)
{
    fstream myFile;
    string line;
    myFile.open(file);
    vector<string> lines;
    myFile.open(file);
    while (getline(myFile, line))
    {
        lines.push_back(line);
    }
    return lines;
}

vector<rewards> createRewards(vector<string> lines)
{
    rewards r;
    string s1 = to_string(r.giftValue);
    string s2 = to_string(r.moneySpent);
    vector<rewards> rewardVector;
    int transactionCount = lines.size() % 5;
    for (int j = 0; j <= lines.size(); j += 5)
    {
        r.gift = lines[j];
        s1 = lines[j + 1];
        s2 = lines[j + 2];
        r.pointsEarned = stof(lines[j + 3]);
        rewardVector.push_back(r);
    }
    return rewardVector;
}

string makeString(vector<string> ids)
{
    string finalString = "";
    for (int i = 0; i < ids.size(); i++)
    {
        if (i != ids.size() - 1)
        {
            finalString += ids[i] + ",";
        }
        else
        {
            finalString += ids[i];
        }
    }
    cout << finalString << endl;
    return finalString;
}

void writeRewards(vector<rewards> rewardVector)
{
    fstream myFile;
    myFile.open("rewards.txt", ios::app);
    for (int i = 0; i <= rewardVector.size(); i++)
    {
        myFile << rewardVector[i].gift << endl;
        myFile << rewardVector[i].giftValue << endl;
        myFile << rewardVector[i].moneySpent << endl;
        myFile << rewardVector[i].pointsEarned << endl;
    }
}

void redeemRewards(vector<rewards> rewardVector)
{
    customer cust;
    string custUN;
    cout << "Enter in your username: " << endl;
    getline(cin, custUN);
    if (cust.custUNPresent(custUN))
    {
        if (cust.retrievePoints(custUN) > rewardVector[1].giftValue)
        {
            int newValue = cust.retrievePoints(custUN) - rewardVector[1].giftValue;
        }
        else
        {
            cout << "You do not have enough reward points for this gift" << endl;
        }
    }
    else
    {
        cout << "This username is not associated with an account" << endl;
    }
}

void redeemable()
{
    redeemRewards(createRewards(readFromFile("rewards.txt")));
}
#endif
