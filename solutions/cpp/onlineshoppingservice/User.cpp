#include "User.hpp"
#include <iostream>

User::User(std::string userId, std::string username, std::string email, std::string address)
    : userId(userId), username(username), email(email), address(address), active(true) {}

User::~User() {
    for (auto order : orders) {
        delete order;
    }
}

std::string User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
std::string User::getAddress() const { return address; }
bool User::isActive() const { return active; }
const std::vector<Order*>& User::getOrders() const { return orders; }

void User::addOrder(Order* order) {
    orders.push_back(order);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    std::cout << "User: " << username << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Total Orders: " << orders.size() << std::endl;
}

void User::displayOrders() const {
    std::cout << "\nOrder History for " << username << ":" << std::endl;
    for (const auto& order : orders) {
        order->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
} 