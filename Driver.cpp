#include <iostream>
#include "BankingProcess.h"

using namespace std;

int main()
{
    BankingProcess Bank;
    Bank.readTransactions("BankTransIn.txt");
    Bank.executeTransactions();
    Bank.Print();
    return 0;
}