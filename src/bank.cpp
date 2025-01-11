// bank.cpp
#include "bank.h"
#include <fstream>
#include <sstream>

Bank::Bank(const std::string& file) : filename(file) {
    loadAccounts();
}

Bank::~Bank() {
    saveAccounts();
}

void Bank::saveAccounts() {
    std::ofstream file(filename);
    if (!file) return;  // Handle file open failure gracefully
    
    for (const auto& [accNum, acc] : accounts) {
        file << acc.toString() << '\n';
    }
}

void Bank::loadAccounts() {
    std::ifstream file(filename);
    if (!file) return;  // Handle file open failure gracefully
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string accNum, name, balStr;
        
        if (std::getline(iss, accNum, ',') &&
            std::getline(iss, name, ',') &&
            std::getline(iss, balStr)) {
            try {
                double balance = std::stod(balStr);
                accounts.emplace(accNum, Account(accNum, name, balance));
            } catch (...) {
                // Skip invalid entries
            }
        }
    }
}

bool Bank::createAccount(const std::string& accNum, const std::string& name) {
    // Check if account already exists
    if (accounts.find(accNum) != accounts.end()) {
        return false;
    }
    
    accounts.emplace(accNum, Account(accNum, name, 0.0));
    return true;
}

bool Bank::deposit(const std::string& accNum, double amount) {
    if (amount <= 0) {
        return false;
    }
    
    auto it = accounts.find(accNum);
    if (it == accounts.end()) {
        return false;
    }
    
    return it->second.deposit(amount);
}

bool Bank::withdraw(const std::string& accNum, double amount) {
    if (amount <= 0) {
        return false;
    }
    
    auto it = accounts.find(accNum);
    if (it == accounts.end()) {
        return false;
    }
    
    return it->second.withdraw(amount);
}

Account* Bank::findAccount(const std::string& accNum) {
    auto it = accounts.find(accNum);
    if (it == accounts.end()) {
        return nullptr;
    }
    return &(it->second);
}