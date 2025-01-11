#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string name;
    double balance;

public:
    Account(std::string accNum, std::string n, double bal = 0.0);
    
    std::string getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;
    
    bool deposit(double amount);
    bool withdraw(double amount);
    std::string toString() const;
};

#endif // ACCOUNT_H