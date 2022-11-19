/*Reward management class - will connect with mainMenu.cpp
 */

#ifndef REWARDMANAGEMENT_H
#define REWARDMANAGEMENT_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class redeemRate
{
private:
  float redRate;

public:
  // default constructor
  redeemRate()
  {
    redRate = .5;
  }

  // utility functions
  void inputRate();
  void logRate();
  void loadRate();

  // setter and getter
  void setRedeemRate(float newRate) { redRate = newRate; }
  float getRedeemRate() { return redRate; }
};

void redeemRate::inputRate()
{
  string newRate = "";
  cout << "Enter the percentage of points the customer should earn per dollar spent: ";
  getline(cin, newRate);
  if (regex_match(newRate, regex("^[0-9][0-9]$")))
  {
    float newPercent = stof(newRate) / 100;
    setRedeemRate(newPercent);
    logRate();
  }
  else
  {
    cout << "Enter the percentage as a whole number." << endl;
    cout << "For example: enter 20 to signify 20%" << endl;
    inputRate();
  }
}

void redeemRate::logRate()
{
  ofstream rateLog;
  rateLog.open("rate.txt");

  rateLog << getRedeemRate() << endl;
  rateLog.close();
}

void redeemRate::loadRate()
{
  ifstream rateLog;
  rateLog.open("rate.txt");

  if (rateLog.is_open())
  {
    string line;
    getline(rateLog, line);
    if (!line.empty())
    {
      float loadRate = stof(line) / 100;
      setRedeemRate(loadRate);
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    cout << "Error reading the log file. Please ensure the file is attached to store the rate information" << endl;
  }

  rateLog.close();
}

// rewards class
class rewards
{
private:
  // declaration of the 2 main variables of the class
  string gift;
  int giftValue;

public:
  // vector initialization
  vector<rewards> rews;

  rewards(){};

  // Function prototypes
  string inputGift();
  int inputGiftValue();
  void rewardValues();
  void initilize();
  void parseData(string);
  void shutdown();
  void logRewards(int);
  bool validateGift(string);
  bool validateGiftValue(int);
  void redeemRewards(customer &);

  // setters
  void setGift(string newGift) { gift = newGift; }
  void setGiftValue(int newGiftValue) { giftValue = newGiftValue; }

  // getters
  string getGift() { return gift; }
  int getGiftValue() { return giftValue; }
};

// Declaration and Assignment of the Variables
void rewards::rewardValues()
{
  rewards newRewards;

  newRewards.setGift(inputGift());
  newRewards.setGiftValue(inputGiftValue());

  rews.push_back(newRewards);

  logRewards(rews.size() - 1);
}

// filling of the rewards.txt file
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
      if (!line.empty())
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

// reading through the rewards.txt file
void rewards::parseData(string line)
{
  string loadG, loadGV;
  rewards loadRew;
  loadG = line.substr(0, line.find_first_of(' '));
  loadRew.setGift(loadG);

  line = line.substr(line.find_first_of(' ') + 1, line.length());
  loadGV = line.substr(0, line.length());
  loadRew.setGiftValue(stoi(loadGV));

  rews.push_back(loadRew);
}

// closing the rewards.txt file
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

  ofstream rewardsLog;
  rewardsLog.open("rewards.txt", ios::app);

  rewardsLog << "Gift: " << gift << endl;
  rewardsLog << "Gift Cost: " << giftValue << endl;

  rewardsLog.close();
}

// inputing the name of the gift, returns the gift name
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
    return inputGift();
  }
}

// inputing the cost of the gift, returns the gift's cost
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
    return inputGiftValue();
  }
}

// Validation of the values
bool rewards::validateGift(string newGift) { return true; }

bool rewards::validateGiftValue(int newGiftValue)
{
  if (isdigit(newGiftValue))
  {
    if (newGiftValue > 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

// Able to check the customer ID and then redeem their points for whatever
// specified reward
void rewards::redeemRewards(customer &cust)
{
  string custUN;
  string reward;
  rewards rewardTemp;
  cout << "Enter in your username: " << endl;
  getline(cin, custUN);
  for (int i = 0; i < rews.size(); i++)
  {
    cout << "Gift: " << rews[i].getGift() << " costs: " << rews[i].getGiftValue() << endl;
  }
  cout << "What gift would you like to reedeem: " << endl;
  getline(cin, reward);
  for (int i = 0; i < rews.size(); i++)
  {
    if (reward == rews[i].gift)
    {
      rewardTemp = rews[i];
    }
    else
    {
    }
  }
  if (cust.custUNPresent(custUN))
  {
    for (int i = 0; i < cust.customers.size(); i++)
    {
      string custUserN = cust.customers[i].getUserName();
      if (custUserN.compare(custUN) == 0)
      {
        customer &tempCust = cust.customers[i];
        if (tempCust.getPoints() > rewardTemp.giftValue)
        {
          int newValue = tempCust.getPoints() - rewardTemp.giftValue;
          tempCust.setPoints(newValue);
          cout << "You have redeemed a Gift!!" << endl;
        }
        else
        {
          cout << "You do not have enough reward points for this gift" << endl;
        }
      }
    }
  }
  else
  {
    cout << "This username is not associated with an account" << endl;
  }
}
#endif
