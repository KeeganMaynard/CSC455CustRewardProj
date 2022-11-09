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
#include <map>
using namespace std;

class rewards
{
private:
    string gift;
    int giftValue;
    int moneySpent;
    int pointsEarned;
   
public:
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

//Declaration and Assignment of the Variables
void rewardValues()
{
    rewards newRewards;

    newRewards.setGift(inputGift());
    newRewards.setGiftValue(inputGiftValue());
    newRewards.setMoneySpent(inputMoneySpent());
    newRewards.setPointsEarned(inputPointsEarned());
    logRewards(newRewards);
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

}



//Writing of the values to the database
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
 
bool validateGift(string newGift)
{
    return true;
}

bool validateGiftValue(int newGiftValue)
{
    if(isdigit(newGiftValue))
    {
        if(newGiftValue > 0)
        {    
            return true;
        }
    }
    else
    {
        return false;
    }
   
}

bool validateMoneySpent(int newMoneySpent)
{
    if(isdigit(newMoneySpent))
    {
        if(newMoneySpent > 0)
        {    
            return true;
        }
    }
    else
    {
        return false;
    }
   
}

bool validatePointsEarned(int newPointsEarned)
{
    if(isdigit(newPointsEarned))
    {
        if(newPointsEarned > 0)
        {    
            return true;
        }
    }
    else
    {
        return false;
    }
}

void redeemRewards(customer newCustomer, rewards newRewards)
{
    int availablePoints = newCustomer.getPoints();
    if (availablePoints > newRewards.getGiftValue())
    {
        availablePoints = availablePoints - newRewards.getGiftValue();
    }
    else
    {
        cout << "You do not have enough reward points for this gift.";
    }

}






#endif
