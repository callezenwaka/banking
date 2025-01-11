// bank.h
#ifndef BANK_H
#define BANK_H

#include <map>
#include <string>
#include "account.h"

class Bank {
private:
    std::map<std::string, Account> accounts;  // Changed from vector to map
    std::string filename;  // Make filename configurable
    
    void saveAccounts();
    void loadAccounts();

public:
    explicit Bank(const std::string& file = "accounts.txt");
    ~Bank();
    
    bool createAccount(const std::string& accNum, const std::string& name);
    bool deposit(const std::string& accNum, double amount);
    bool withdraw(const std::string& accNum, double amount);
    Account* findAccount(const std::string& accNum);
};

#endif // BANK_H