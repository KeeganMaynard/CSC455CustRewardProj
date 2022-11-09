/*Reward management class - will connect with mainMenu.cpp
    this service allows the manager to specify the following
    - the number of points awarded for a given shopping amount
    - the gifts that can be redeemed given the total number of reward points
    - will need function that determine if redeem points are enough
        - ie. function to check if points cost > customer points
*/
#ifndef REWARDMANAGEMENT_H
#define REWARDMANAGEMENT_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Declaration and Assignment of the Variables
void rewardValues()
{
   string gift;
   int giftValue, moneySpent, pointsEarned;
   gift = inputGift();
   giftValue = inputGiftValue();
   moneySpent = inputMoneySpent();
   pointsEarned = inputPointsEarned();
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
void rewardDatabase(string gift, int giftValue, int moneySpent, int pointsEarned)
{
    ofstream rewardsLog("rewards.txt");
    rewardsLog << "Reward Gift: " << gift << " Gift Cost: " << giftValue << endl;
    rewardsLog << "Money Spent by Customer: " << moneySpent << " Reward Points Earned: " << pointsEarned << endl;

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






#endif
