#include "account.h"

Account::Account(std::string accNum, std::string n, double bal)
    : accountNumber(accNum), name(n), balance(bal) {}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getName() const {
    return name;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

std::string Account::toString() const {
    return accountNumber + "," + name + "," + std::to_string(balance);
}