/*Reward management class - will connect with mainMenu.cpp
    this service allows the manager to specify the following
    - the number of points awarded for a given shopping amount
    - the gifts that can be redeemed given the total number of reward points
    - will need function that determine if redeem points are enough
        - ie. function to check if points cost > customer points
*/

#ifndef REWARDMANAGEMENT_H
#define REWARDMANAGEMENT_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//rewards class
class rewards
{
private:
    //declaration of the 4 main variables of the class
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

//filling of the rewards.txt file
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

//reading through the rewards.txt file
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

//closing the rewards.txt file
void rewards::shutdown()
{
    ofstream logFile("rewards.txt");
    logFile.close();

    for (int i = 0; i < rews.size(); i++)
    {
        logRewards(i);
    }
}

// assigning the rewards.txt file to its vector
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

//inputing the name of the gift, returns the gift name
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

//inputing the cost of the gift, returns the gift's cost
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

//inputing the customers money spent, returns the value that they spent
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

//inputing the points received for the price earned, returns the amount of points earned
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

//Validation of the values
bool rewards::validateGift(string newGift)
{
    return true;
}

bool rewards::validateGiftValue(int newGiftValue)
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

bool rewards::validateMoneySpent(int newMoneySpent)
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

bool rewards::validatePointsEarned(int newPointsEarned)
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

//Able to check the customer ID and then redeem their points for whatever specified reward
void rewards::redeemRewards()
{
    customer cust;
    string custUN;
    string reward;
    rewards rewardTemp;
    cout << "Enter in your username: " << endl;
    getline(cin, custUN);
    cout << "What gift would you like to reedeem?: " << endl;
    getline(cin, reward);
    for(int i = 0; i < rews.size(); i++){
        if (reward == rews[i].gift){
            rewardTemp = rews[i];
        }
        else{}
    }
    if (cust.custUNPresent(custUN)){
        if (cust.retrievePoints(custUN) > rewardTemp.giftValue){
            int newValue = cust.retrievePoints(custUN) - rewardTemp.giftValue;
            cout << "You have redeemed a Gift!!" << endl;
        }
        else{
            cout << "You do not have enough reward points for this gift" << endl;
        }
    }
    else{
        cout << "This username is not associated with an account" << endl;
    }
}
#endif
