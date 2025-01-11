#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include "account.h"

class Bank {
private:
    std::vector<Account> accounts;
    const std::string FILENAME = "accounts.txt";
    
    void saveAccounts();
    void loadAccounts();

public:
    Bank();
    ~Bank();
    
    bool createAccount(const std::string& accNum, const std::string& name);
    bool deposit(const std::string& accNum, double amount);
    bool withdraw(const std::string& accNum, double amount);
    Account* findAccount(const std::string& accNum);
};

#endif // BANK_H