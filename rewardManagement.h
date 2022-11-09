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
public:
    rewards();
    string gift;
    int giftValue;
    int moneySpent;
    int pointsEarned;
   

};
//Declaration and Assignment of the Variables
void rewardValues()
{
   rewards newRewards;
   newRewards.gift = inputGift();
   newRewards.giftValue = inputGiftValue();
   newRewards.moneySpent = inputMoneySpent();
   newRewards.pointsEarned = inputPointsEarned();
   rewardDatabase(newRewards);
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
void rewardDatabase(rewards rewardLog)
{
    ofstream rewardsLog("rewards.txt");
    rewardsLog << "Reward Gift: " << rewardLog.gift << " Gift Cost: " << rewardLog.giftValue << endl;
    rewardsLog << "Money Spent by Customer: " << rewardLog.moneySpent << " Reward Points Earned: " << rewardLog.pointsEarned << endl;

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
    if (availablePoints > newRewards.giftValue)
    {
        availablePoints = availablePoints - newRewards.giftValue;
    }

}






#endif
