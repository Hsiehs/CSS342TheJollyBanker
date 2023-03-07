#pragma once
#include <string>
#include <fstream>
#include "Transaction.h"
#include "Fund.h"
using namespace std;

const int FUND_SIZE = 10;


class Account{
private:
    int accountNum, balance;
    string firstName, lastName;
    
public:
    Fund fundArray[FUND_SIZE];
    //Constructor
    Account();
    Account(string firstName, string lastName, int accountNum);
    ~Account();

    //Getters/Setters
    string getFirstName();
    string getLastName();
    int getAccountNum();
    int getBalance(int fundNum);

    //Operation
    void printTransaction(int fundNum, ofstream &output);


};