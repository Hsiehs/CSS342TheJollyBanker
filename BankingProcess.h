#pragma once
#include <string>
#include <queue>
#include <iostream>
#include "BSTree.h"
#include "Transaction.h"
using namespace std;

class BankingProcess
{
private:
    string fileName;
    queue<Transaction> QueueList;
    BSTree accountList;

public:
    string fundTypes[10] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};
    void readTransactions(string fileName);
    void executeTransactions();
    void Print();
};
