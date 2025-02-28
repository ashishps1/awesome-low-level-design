#include "User.hpp"
#include <iostream>

User::User(std::string userId, std::string name, std::string email, std::string phoneNumber)
    : userId(userId), name(name), email(email), phoneNumber(phoneNumber) {}

std::string User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPhoneNumber() const { return phoneNumber; }

void User::displayInfo() const {
    std::cout << "User: " << name << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phoneNumber << std::endl;
} 