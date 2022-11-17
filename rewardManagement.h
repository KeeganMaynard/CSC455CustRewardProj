/*Reward management class - will connect with mainMenu.cpp
    this service allows the manager to specify the following
    - the number of points awarded for a given shopping amount
    - the gifts that can be redeemed given the total number of reward points
    - will need function that determine if redeem points are enough
        - ie. function to check if points cost > customer points
*/
//this is my change again...
#ifndef REWARDMANAGEMENT_H
#define REWARDMANAGEMENT_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class rewards
{
private:
    string gift;
    int giftValue;
    int moneySpent;
    int pointsEarned;

public:

    //vector initialization
    vector<rewards> rews;

    rewards(){};

    // Function prototypes
    string inputGift();
    int inputGiftValue();
    void rewardValues();
    void initilize();
    void parseData(string);
    int inputMoneySpent();
    int inputPointsEarned();
    void shutdown();
    void logRewards(int);
    bool validateGift(string);
    bool validateGiftValue(int);
    bool validateMoneySpent(int);
    bool validatePointsEarned(int);
    void redeemRewards();

    //setters
    void setGift(string newGift) { gift = newGift; }
    void setGiftValue(int newGiftValue) { giftValue = newGiftValue; }
    void setMoneySpent(int newMoneySpent) { moneySpent = newMoneySpent; }
    void setPointsEarned(int newPointsEarned) { pointsEarned = newPointsEarned; }

    //getters
    string getGift() { return gift; }
    int getGiftValue() { return giftValue; }
    int getMoneySpent() { return moneySpent; }
    int getPointsEarned() { return pointsEarned; }
};



// Declaration and Assignment of the Variables
void rewards::rewardValues()
{
    rewards newRewards;

    newRewards.setGift(inputGift());
    newRewards.setGiftValue(inputGiftValue());
    newRewards.setMoneySpent(inputMoneySpent());
    newRewards.setPointsEarned(inputPointsEarned());
    
    rews.push_back(newRewards);

    logRewards(rews.size() - 1);


}

void rewards::initilize()
{
    ifstream rewardLog;
    rewardLog.open("rewards.txt");

    if (rewardLog.is_open())
    {
        string line;
        string temp;
        string buffer;
        while (getline(rewardLog, line))
        {
            if(!line.empty())
            {
                temp = line.substr(line.find_last_of(' ') + 1, line.length());
                buffer = buffer + temp + " ";
            }
            else
            {
                parseData(buffer);
                temp = "";
                buffer = "";
            }
        }
        rewardLog.close();
    }
    else
    {
        cout << "Error reading the rewards file." << endl;
    }
}

void rewards::parseData(string line)
{
    string loadG, loadGV, loadMS, loadPE;
    rewards loadRew;
    loadG = line.substr(0, line.find_first_of(' '));
    loadRew.setGift(loadG);

    line = line.substr(line.find_first_of(' ') + 1, line.length());
    loadGV = line.substr(0, line.find_first_of(' '));
    loadRew.setGiftValue(stoi(loadGV));

    line = line.substr(line.find_first_of(' ') + 1, line.length());
    loadMS = line.substr(0, line.find_first_of(' '));
    loadRew.setMoneySpent(stoi(loadMS));

    line = line.substr(line.find_first_of(' ') + 1, line.length());
    loadPE = line.substr(0, line.find_first_of(' '));
    loadRew.setPointsEarned(stoi(loadPE));

    rews.push_back(loadRew);
    

}

void rewards::shutdown()
{
    ofstream logFile("rewards.txt");
    logFile.close();

    for (int i = 0; i < rews.size(); i++)
    {
        logRewards(i);
    }
}

void rewards::logRewards(int rewNum)
{
    string &gift = rews[rewNum].gift;
    int &giftValue = rews[rewNum].giftValue;
    int &moneySpent = rews[rewNum].moneySpent;
    int &pointsEarned = rews[rewNum].pointsEarned;

    ofstream rewardsLog;
    rewardsLog.open("rewards.txt", ios::app);

    rewardsLog << "Gift: " << gift << endl;
    rewardsLog << "Gift Cost: " << giftValue << endl;
    rewardsLog << "Money Spent: " << moneySpent << endl;
    rewardsLog << "Points Earned: " << pointsEarned << endl;

    rewardsLog.close();
}


string rewards::inputGift()
{
    string gift = "";
    cout << "Enter the available reward gift: ";
    getline(cin, gift);
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

int rewards::inputGiftValue()
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

int rewards::inputMoneySpent()
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

int rewards::inputPointsEarned()
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
#endif
