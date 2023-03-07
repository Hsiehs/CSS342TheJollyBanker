#include "BankingProcess.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

// reads from txt file, creates transaction objects and stores them into queue.
void BankingProcess::readTransactions(string filename)
{
    ifstream myfile;

    myfile.open(filename);

    if (!myfile)
    {
        cerr << "File not open!" << endl;
    }

    while (myfile)
    {
        string line;
        getline(myfile, line);
        istringstream iss(line);
        char actionType;
        iss >> actionType;
        if (line.empty())
        {
            break;
        }
        // sample input: O Cash Johnny 1001
        if (actionType == 'O')
        {
            string firstName, lastName;
            int accountNum;
            iss >> firstName >> lastName >> accountNum;
            Transaction Q(actionType, firstName, lastName, accountNum);
            QueueList.push(Q);
        }

        // sample input: D 10010 542

        if (actionType == 'D' || actionType == 'W')
        {
            int ID, fundNum, accountNum, amount;
            iss >> ID >> amount;
            accountNum = ID / 10;
            fundNum = ID % 10;
            Transaction Q(actionType, accountNum, fundNum, amount);
            QueueList.push(Q);
        }

        // sample input: T 10017 54 10015

        if (actionType == 'T')
        {
            int ID, accountNum, fundNum, amount, toID, toAccountNum, toFundNum;
            iss >> ID >> amount >> toID;
            accountNum = ID / 10;
            fundNum = ID % 10;
            toAccountNum = toID / 10;
            toFundNum = toID % 10;
            Transaction Q(actionType, accountNum, fundNum, amount, toAccountNum, toFundNum);
            QueueList.push(Q);
        }

        // sample input: H 1253
        if (actionType == 'H')
        {
            int ID, accountNum, fundNum;
            iss >> ID;
            if (log10(ID) + 1 < 5)
            {
                accountNum = ID;
                fundNum = -1;
                Transaction Q(actionType, accountNum, fundNum);
                QueueList.push(Q);
            }
            else
            {
                accountNum = ID / 10;
                fundNum = ID % 10;
                Transaction Q(actionType, accountNum, fundNum);
                QueueList.push(Q);
            }
        }
    }
    myfile.close();
}

// reads through the queue and processes each transaction.
void BankingProcess::executeTransactions()
{
    bool flag = true;
    ofstream outputFile("BankTransOut.txt");
    while (flag)
    {
        Transaction currentTrans = QueueList.front();
        char actionType;
        actionType = currentTrans.getActionType();

        // Create account with name and id
        // add it to binaryTree
        if (actionType == 'O')
        {
            Account *A = new Account(currentTrans.getFirstName(), currentTrans.getLastName(), currentTrans.getAccountNum());
            accountList.Insert(A);
        }

        // checks that account exists and deposits it into the correct account->fund type

        else if (actionType == 'D')
        {
            int accountNum = currentTrans.getAccountNum();
            int fundNum = currentTrans.getFundNum();
            int amount = currentTrans.getAmount();
            Account *A = new Account();
            accountList.Retrieve(accountNum, A);
            A->fundArray[fundNum].addFunds(amount);
            A->fundArray[fundNum].recordTransaction(currentTrans);
        }

        // checks account exists and enough balance to cover withdraw, if not check other linked fund type.

        else if (actionType == 'W')
        {
            int accountNum = currentTrans.getAccountNum();
            int fundNum = currentTrans.getFundNum();
            int amount = currentTrans.getAmount();
            Account *A = new Account();
            accountList.Retrieve(accountNum, A);
            if (amount <= A->fundArray[fundNum].getBalance())
            {
                A->fundArray[fundNum].minusFunds(amount);
                A->fundArray[fundNum].recordTransaction(currentTrans);
            }

            if (amount > A->fundArray[fundNum].getBalance())
            {
                if (fundNum == 0 || fundNum == 2)
                {
                    if (amount > (A->fundArray[fundNum].getBalance() + A->fundArray[fundNum + 1].getBalance()))
                    {
                        currentTrans.setFailed(true);
                        A->fundArray[fundNum].recordTransaction(currentTrans);
                    }
                    else
                    {
                        int newBalance = A->fundArray[fundNum].getBalance();
                        A->fundArray[fundNum].setBalance(0);
                        amount = amount - newBalance;
                        A->fundArray[fundNum + 1].minusFunds(amount);
                        currentTrans.setBalance(newBalance);
                        Transaction newTrans(actionType, accountNum, fundNum + 1, amount);
                        A->fundArray[fundNum].recordTransaction(currentTrans);
                        A->fundArray[fundNum + 1].recordTransaction(newTrans);
                    }
                }
                else if (fundNum == 1 || fundNum == 3)
                {
                    if (amount > (A->fundArray[fundNum].getBalance() + A->fundArray[fundNum - 1].getBalance()))
                    {
                        currentTrans.setFailed(true);
                        A->fundArray[fundNum].recordTransaction(currentTrans);
                    }
                    else
                    {
                        int newBalance = A->fundArray[fundNum].getBalance();
                        A->fundArray[fundNum].setBalance(0);
                        amount = amount - newBalance;
                        A->fundArray[fundNum - 1].minusFunds(amount);
                        currentTrans.setBalance(newBalance);
                        Transaction newTrans(actionType, accountNum, fundNum - 1, amount);
                        A->fundArray[fundNum].recordTransaction(currentTrans);
                        A->fundArray[fundNum - 1].recordTransaction(newTrans);
                    }
                }
                else
                {
                    currentTrans.setFailed(true);
                    outputFile << "ERROR: Not enough funds to withdraw " << amount << " from " << A->getFirstName() << " " << A->getLastName() << " " << fundTypes[fundNum] << endl;
                    A->fundArray[fundNum].recordTransaction(currentTrans);
                }
            }
        }

        // Handles transfers between accounts

        else if (actionType == 'T')
        {
            int accountNum = currentTrans.getAccountNum();
            int fundNum = currentTrans.getFundNum();
            int amount = currentTrans.getAmount();
            int toAccountNum = currentTrans.getToAccountNum();
            int toFundNum = currentTrans.getToFundNum();
            Account *A = new Account();
            Account *B = new Account();
            bool accountA = accountList.Retrieve(accountNum, A);
            bool accountB = accountList.Retrieve(toAccountNum, B);
            if(accountA && accountB)
            {
                A->fundArray[fundNum].minusFunds(amount);
                B->fundArray[toFundNum].addFunds(amount);
                A->fundArray[fundNum].recordTransaction(currentTrans);
                B->fundArray[toFundNum].recordTransaction(currentTrans);
            }
        }

        // Print the transaction history for specific fund or entire account.

        else if (actionType == 'H')
        {
            int accountNum = currentTrans.getAccountNum();
            Account *A = new Account();
            accountList.Retrieve(accountNum, A);
            if (currentTrans.getFundNum() < 0)
            {
                outputFile << "Transaction History for " << A->getFirstName() << " " << A->getLastName() << " by fund." << endl;
                for (int i = 0; i < 10; i++)
                {
                    if (A->fundArray[i].transHistory.size() > 0)
                    {
                        outputFile << fundTypes[i] << ": $" << A->fundArray[i].getBalance() << endl;
                        A->printTransaction(i, outputFile);
                    }
                }
            }
            else
            {
                outputFile << "Transaction History for " << A->getFirstName() << " " << A->getLastName() << " " << fundTypes[currentTrans.getFundNum()] << ": $" << A->fundArray[currentTrans.getFundNum()].getBalance() << endl;
                A->printTransaction(currentTrans.getFundNum(), outputFile);
            }
        }
        QueueList.pop();

        if (QueueList.empty())
        {
            flag = false;
        }
    }
    outputFile.close();
}

// Displays all the existing accounts, funds, and their balances.
void BankingProcess::Print()
{
    ofstream outputFile("BankTransOut.txt", std::ios_base::app);
    outputFile << "Processing Done. Final Balances" << endl;
    accountList.Display(accountList.root);
}