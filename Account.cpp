#include "Account.h"
#include "Fund.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Account::Account()
{
}

Account::Account(string firstName, string lastName, int accountNum)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->accountNum = accountNum;
}

Account::~Account()
{
}

// Getter functions
string Account::getFirstName()
{
    return firstName;
}

string Account::getLastName()
{
    return lastName;
}

int Account::getAccountNum()
{
    return accountNum;
}

int Account::getBalance(int fundNum)
{
    int balance = fundArray[fundNum].getBalance();
    return balance;
}


//prints each transaction in the funds transaction history vector.
void Account::printTransaction(int fundNum, ofstream &output)
{
    for (int i = 0; i < fundArray[fundNum].transHistory.size(); i++)
    {
        if (fundArray[fundNum].transHistory[i].getFailed() == true)
        {
            output << "    " << fundArray[fundNum].transHistory[i] << " (failed)" << endl;
        }
        else
        {
            output << "    " << fundArray[fundNum].transHistory[i] << endl;
        }
    }
}