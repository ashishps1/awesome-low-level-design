#include "User.hpp"
#include <iostream>
#include <iomanip>

User::User(std::string userId, std::string name, std::string email)
    : userId(userId), name(name), email(email), active(true) {}

std::string User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
bool User::isActive() const { return active; }
double User::getBalanceWith(const std::string& userId) const {
    auto it = balances.find(userId);
    return it != balances.end() ? it->second : 0.0;
}
const std::map<std::string, double>& User::getBalances() const { return balances; }

void User::updateBalance(const std::string& userId, double amount) {
    balances[userId] += amount;
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << name << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
}

void User::displayBalances() const {
    std::cout << "\nBalances for " << name << ":" << std::endl;
    for (const auto& balance : balances) {
        std::cout << "With " << balance.first << ": $"
                  << std::fixed << std::setprecision(2) << balance.second << std::endl;
    }
} 