#pragma once
#include "Account.h"

using namespace std;

class BSTree{
private:
    struct Node
    {
        Account *pAcct;
        Node *right;
        Node *left;
    };
    
    
public:
    BSTree();
    ~BSTree();
    string fundTypes [10] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund","Growth Index Fund", "Value Fund", "Value Stock Index"};

    Node* root;

    bool Insert(Account *);
    bool RecursiveInsert(Account *, Node *);
    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Retrieve(const int &, Account * &) const;
    
    // displays the contents of a tree to cout
    void Display(Node* node) const;
    void Empty(); 
    bool isEmpty() const; 

};