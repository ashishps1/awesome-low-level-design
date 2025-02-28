#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string pin;
    double balance;

public:
    Account(std::string accountNumber, std::string pin, double initialBalance = 0.0);
    
    std::string getAccountNumber() const;
    bool validatePin(const std::string& inputPin) const;
    double getBalance() const;
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void displayBalance() const;
};

#endif 