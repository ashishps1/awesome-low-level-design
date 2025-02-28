#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Portfolio.hpp"

class User {
private:
    std::string userId;
    std::string username;
    std::string email;
    double balance;
    Portfolio* portfolio;
    bool active;

public:
    User(std::string userId, std::string username, std::string email);
    ~User();
    
    std::string getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    double getBalance() const;
    Portfolio* getPortfolio() const;
    bool isActive() const;
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 