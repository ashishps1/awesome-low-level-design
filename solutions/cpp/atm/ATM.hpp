#ifndef ATM_HPP
#define ATM_HPP

#include "Account.hpp"
#include <vector>
#include <string>

class ATM {
private:
    std::vector<Account*> accounts;
    Account* currentAccount;
    bool isAuthenticated;

public:
    ATM();
    ~ATM();
    
    void addAccount(Account* account);
    bool authenticate(const std::string& accountNumber, const std::string& pin);
    void logout();
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void checkBalance() const;
    
    void displayMenu() const;
    void start();
};

#endif 