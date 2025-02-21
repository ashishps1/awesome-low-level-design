#include "Account.hpp"
#include <iostream>
#include <iomanip>

Account::Account(std::string accountNumber, std::string pin, double initialBalance)
    : accountNumber(accountNumber), pin(pin), balance(initialBalance) {}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

bool Account::validatePin(const std::string& inputPin) const {
    return pin == inputPin;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    return true;
}

void Account::displayBalance() const {
    std::cout << "Current balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
} 