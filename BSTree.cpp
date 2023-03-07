#include "BSTree.h"
#include <iostream>
#include <fstream>
using namespace std;

BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    delete root;
    root = nullptr;
}

// Insert a new account into the binary tree
bool BSTree::Insert(Account *nAccount)
{

    if (root == nullptr)
    {
        root = new Node;
        root->pAcct = nAccount;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    else
    {
        Node *curNode = root;
        RecursiveInsert(nAccount, curNode);
    }
    return false;
}


//A recursive method to place all the account in a sorted order
bool BSTree::RecursiveInsert(Account *nAccount, Node *curNode)
{
    // new account id < current account id, left
    //  if the node is null, take that place
    //  if not, keep going to the left
    ofstream output;
    output.open("BankTransOut.txt", std::ios_base::app);

    if (nAccount->getAccountNum() < curNode->pAcct->getAccountNum())
    {
        if (curNode->left == nullptr)
        {
            Node *nNode = new Node();
            nNode->pAcct = nAccount;
            nNode->left = nullptr;
            nNode->right = nullptr;
            curNode->left = nNode;
            return true;
        }
        else
        {
            return RecursiveInsert(nAccount, curNode->left);
        }
    }
    else if (nAccount->getAccountNum() > curNode->pAcct->getAccountNum())
    {
        if (curNode->right == nullptr)
        {
            Node *nNode = new Node();
            nNode->pAcct = nAccount;
            nNode->left = nullptr;
            nNode->right = nullptr;
            curNode->right = nNode;
            return true;
        }
        else
        {
            return RecursiveInsert(nAccount, curNode->right);
        }
    }
    else
    {
        output << "ERROR: Account " << nAccount->getAccountNum() << " is already open. Transaction refused." << endl;
        return false;
    }
}


// check to see if an account already exists in the BSTree
bool BSTree::Retrieve(const int &accountNum, Account *&nAccount) const
{
    ofstream output;
    output.open("BankTransOut.txt", std::ios_base::app);
    Node *current = root;
    bool search = false;
    while (!search)
    {
        if (current != nullptr && accountNum == current->pAcct->getAccountNum())
        {
            search = true;
            nAccount = current->pAcct;
            return search;
        }
        else if (current != nullptr && accountNum > current->pAcct->getAccountNum())
        {
            current = current->right;
        }
        else if (current != nullptr && accountNum < current->pAcct->getAccountNum())
        {
            current = current->left;
        }
        else
        {
            search = true;
        }
    }
    output << "ERROR: Account " << accountNum << " not found. Transaction refused." << endl;
    return false;
}

// prints out all the accounts and their funds
void BSTree::Display(Node *node) const
{

    if (node == nullptr)
    {
        return;
    }

    ofstream fin;
    fin.open("BankTransOut.txt", std::ios_base::app);
    Display(node->left);
    Account *A = node->pAcct;
    fin << A->getFirstName() << " " << A->getLastName() << " Account ID: " << A->getAccountNum() << endl;
    for (int i = 0; i < 10; i++)
    {
        fin << "    " << fundTypes[i] << ": $" << A->fundArray[i].getBalance() << endl;
    }
    fin << endl;
    fin.close();
    Display(node->right);
}