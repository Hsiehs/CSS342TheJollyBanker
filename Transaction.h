#pragma once
#include <string>

using namespace std;

class Transaction
{
private:
    string firstName, lastName;
    int accountNum, toAccountNum;
    int fundNum, toFundNum, amount;
    char actionType;
    bool failed = false;

public:
    // Constructor
    Transaction(char actionType, int accountNum);
    Transaction(char actionType, int accountNum, int fundNum);
    Transaction(char actionType, int accountNum, int fundNum, int amount);
    Transaction(char actionType, string firstName, string lastName, int accountNum);
    Transaction(char actionType, int accountNum, int fundNum, int amount, int toAccountNum, int toFundNum);

    // Operator overload
    friend ostream &operator<<(ostream &os, Transaction &transaction);

    // Getters
    char getActionType();
    int getAccountNum();
    int getFundNum();
    int getAmount();
    int getToAccountNum();
    int getToFundNum();
    bool getFailed();
    string getFirstName();
    string getLastName();

    // Setters
    void setFailed(bool x);
    void setBalance(int x);
};