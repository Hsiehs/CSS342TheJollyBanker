Welcome to The Jolly Banker
Created by Team 10
Stanley Hsieh, Fang Wu, George Vu
UWB CSS342 Program 5 
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Contributions
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Fang Wu                         George Vu                           Stanley Hsieh
BankingProcess.cpp/.h           Account.cpp/.h                      Fund.cpp/.h 
BSTree.cpp/.h (insert)          BSTree.cpp/.h (Retrieve)            Transaction.cpp/.h 
Troubleshooting                                                     BSTree.cpp/.h (Display)
.                                                                   Troubleshooting

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

This program reads from a input file ("BankTransIn.txt") and pushes every transaction into a queue.
The program then goes through the queue and calculates every transaction. (open account, deposit, withdraw, transfer, and history).
When opening new account, the account is stored into a binary search tree (BSTree). 
Each node of the BSTree stores an Account object, that keeps track of the account number, first name, last name, and a array of funds objects and can be retrieved to use.
Each fund objects stores the specific fund number, balance, and a vector that stores transaction objects (transaction history).
After each transaction, weather it fails or not, it is saved into a vector that keeps tracks of all the transactions.
When the queue has been depleted, the program will print out all of the existing account and funds with their corresponding balances.
