#include <iostream>
#include "Fund.h"
using namespace std;

Fund::Fund()
{
    this->balance = 0;
}

Fund::~Fund()
{
}

// Get Balance function
int Fund::getBalance()
{
    return balance;
}

// Set Balance function
void Fund::setBalance(int amount)
{
    balance = amount;
}

// adds funds to specified funds
void Fund::addFunds(int amount)
{
    int newBalance = getBalance() + amount;
    setBalance(newBalance);
}

// subtracts funds to specified funds
void Fund::minusFunds(int amount)
{
    int newBalance = getBalance() - amount;
    setBalance(newBalance);
}

// records the transaction into the transaction history for specified fund.
void Fund::recordTransaction(Transaction history)
{
    transHistory.push_back(history);
}
