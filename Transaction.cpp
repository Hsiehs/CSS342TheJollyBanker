#include <ostream>
#include "Transaction.h"

using namespace std;

// Constructors

Transaction::Transaction(char actionType, int accountNum, int fundNum, int amount)
{
    this->actionType = actionType;
    this->accountNum = accountNum;
    this->fundNum = fundNum;
    this->amount = amount;
    this->failed = false;
};

Transaction::Transaction(char actionType, int accountNum, int fundNum, int amount, int toAccountNum, int toFundNum)
{
    this->actionType = actionType;
    this->accountNum = accountNum;
    this->fundNum = fundNum;
    this->amount = amount;
    this->toAccountNum = toAccountNum;
    this->toFundNum = toFundNum;
    this->failed = false;
}

Transaction::Transaction(char actionType, string firstName, string lastName, int accountNum)
{
    this->actionType = actionType;
    this->firstName = firstName;
    this->lastName = lastName;
    this->accountNum = accountNum;
    this->failed = false;
}

Transaction::Transaction(char actionType, int accountNum, int fundNum)
{
    this->actionType = actionType;
    this->accountNum = accountNum;
    this->fundNum = fundNum;
    this->failed = false;
}

Transaction::Transaction(char actionType, int accountNum)
{
    this->actionType = actionType;
    this->accountNum = accountNum;
    this->fundNum;
    this->failed = false;
}

// Operator Overload

ostream &operator<<(ostream &os, Transaction &transaction)
{
    if (transaction.getActionType() == 'T')
    {
        os << transaction.getActionType() << " " << transaction.getAccountNum() << transaction.getFundNum() << " " << transaction.getAmount() << " " << transaction.getToAccountNum() << transaction.getToFundNum();
    }
    else
    {
        os << transaction.getActionType() << " " << transaction.getAccountNum() << transaction.getFundNum() << " " << transaction.getAmount();
    }
    return os;
}

// Getters

char Transaction::getActionType()
{
    return actionType;
}

int Transaction::getAccountNum()
{
    return accountNum;
}

int Transaction::getFundNum()
{
    return fundNum;
}
int Transaction::getToFundNum()
{
    return toFundNum;
}

int Transaction::getAmount()
{
    return amount;
}

int Transaction::getToAccountNum()
{
    return toAccountNum;
}

bool Transaction::getFailed()
{
    return failed;
}

string Transaction::getFirstName()
{
    return firstName;
}

string Transaction::getLastName()
{
    return lastName;
}

// Setter

void Transaction::setFailed(bool x)
{
    this->failed = x;
}

void Transaction::setBalance(int x)
{
    this->amount = x;
}