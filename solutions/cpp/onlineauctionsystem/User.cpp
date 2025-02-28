#include "User.hpp"
#include <iostream>
#include <iomanip>

User::User(std::string userId, std::string username, std::string email)
    : userId(userId), username(username), email(email), balance(0.0), active(true) {}

User::~User() {
    // Note: Items are managed by the auction system
    listedItems.clear();
    purchasedItems.clear();
}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
double User::getBalance() const { return balance; }
bool User::isActive() const { return active; }
const std::vector<Item*>& User::getListedItems() const { return listedItems; }
const std::vector<Item*>& User::getPurchasedItems() const { return purchasedItems; }

void User::addBalance(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool User::deductBalance(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void User::addListedItem(Item* item) {
    listedItems.push_back(item);
}

void User::addPurchasedItem(Item* item) {
    purchasedItems.push_back(item);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Listed Items: " << listedItems.size() << std::endl;
    std::cout << "Purchased Items: " << purchasedItems.size() << std::endl;
} 