#pragma once
#include <string>
#include <vector>
#include "Transaction.h"
using namespace std;

class Fund
{
private:
    int fundNum;
    int balance;

public:
    vector<Transaction> transHistory;
    Fund();
    ~Fund();

    int getBalance();
    void setBalance(int amount);
    void addFunds(int amount);
    void minusFunds(int amount);
    void transfer(int toID, int fundNum, int amount);
    void recordTransaction(Transaction history);
};
