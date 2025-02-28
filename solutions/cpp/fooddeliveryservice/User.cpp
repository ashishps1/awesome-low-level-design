#include "User.hpp"
#include <iostream>

User::User(std::string userId, std::string name, std::string email, 
           std::string phone, std::string address)
    : userId(userId), name(name), email(email), phone(phone), address(address) {}

std::string User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPhone() const { return phone; }
std::string User::getAddress() const { return address; }

void User::displayInfo() const {
    std::cout << "User: " << name << " (ID: " << userId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Address: " << address << std::endl;
} 