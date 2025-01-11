#include <iostream>
#include <iomanip>
#include "bank.h"

int main() {
    Bank bank;
    std::string choice;
    
    while (true) {
        std::cout << "\nBanking System Menu:\n"
                  << "1. Create Account\n"
                  << "2. Deposit\n"
                  << "3. Withdraw\n"
                  << "4. Check Balance\n"
                  << "5. Exit\n"
                  << "Enter choice: ";
        
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string accNum, name;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accNum);
            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            if (bank.createAccount(accNum, name)) {
                std::cout << "Account created successfully!\n";
            } else {
                std::cout << "Account already exists!\n";
            }
        }
        else if (choice == "2") {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accNum);
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            std::cin.ignore();

            if (bank.deposit(accNum, amount)) {
                std::cout << "Deposit successful!\n";
            } else {
                std::cout << "Invalid account or amount!\n";
            }
        }
        else if (choice == "3") {
            std::string accNum;
            double amount;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accNum);
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            std::cin.ignore();

            if (bank.withdraw(accNum, amount)) {
                std::cout << "Withdrawal successful!\n";
            } else {
                std::cout << "Invalid account, amount, or insufficient funds!\n";
            }
        }
        else if (choice == "4") {
            std::string accNum;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accNum);

            Account* acc = bank.findAccount(accNum);
            if (acc) {
                std::cout << "Account Details:\n"
                         << "Account Number: " << acc->getAccountNumber() << "\n"
                         << "Name: " << acc->getName() << "\n"
                         << "✨ Balance: $" << std::fixed << std::setprecision(2) 
                         << acc->getBalance() << "\n";
            } else {
                std::cout << "Account not found!\n";
            }
        }
        else if (choice == "5") {
            std::cout << "Thank you for using our banking system!\n";
            break;
        }
        else {
            std::cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}