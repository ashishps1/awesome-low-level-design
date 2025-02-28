#include "User.hpp"
#include <iostream>
#include <iomanip>

User::User(std::string userId, std::string username, std::string email)
    : userId(userId), username(username), email(email), balance(0.0), active(true) {
    portfolio = new Portfolio(userId);
}

User::~User() {
    delete portfolio;
}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
double User::getBalance() const { return balance; }
Portfolio* User::getPortfolio() const { return portfolio; }
bool User::isActive() const { return active; }

bool User::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool User::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    portfolio->displayInfo();
} 