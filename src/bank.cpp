#include "bank.h"
#include <fstream>
#include <sstream>

Bank::Bank() {
    loadAccounts();
}

Bank::~Bank() {
    saveAccounts();
}

void Bank::saveAccounts() {
    std::ofstream file(FILENAME);
    for (const Account& acc : accounts) {
        file << acc.toString() << '\n';
    }
}

void Bank::loadAccounts() {
    std::ifstream file(FILENAME);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string accNum, name, balStr;
        
        if (std::getline(iss, accNum, ',') &&
            std::getline(iss, name, ',') &&
            std::getline(iss, balStr)) {
            try {
                double balance = std::stod(balStr);
                accounts.emplace_back(accNum, name, balance);
            } catch (...) {
                // Skip invalid entries
            }
        }
    }
}

bool Bank::createAccount(const std::string& accNum, const std::string& name) {
    // Check if account already exists
    if (findAccount(accNum) != nullptr) {
        return false;
    }
    
    accounts.emplace_back(accNum, name, 0.0);
    return true;
}

bool Bank::deposit(const std::string& accNum, double amount) {
    // Invalid amount check
    if (amount <= 0) {
        return false;
    }
    
    for (Account& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return acc.deposit(amount);
        }
    }
    return false;  // Account not found
}

bool Bank::withdraw(const std::string& accNum, double amount) {
    // Invalid amount check
    if (amount <= 0) {
        return false;
    }
    
    for (Account& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return acc.withdraw(amount);
        }
    }
    return false;  // Account not found
}

Account* Bank::findAccount(const std::string& accNum) {
    for (Account& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}