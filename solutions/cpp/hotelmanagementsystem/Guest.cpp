#include "Guest.hpp"
#include <iostream>

Guest::Guest(std::string guestId, std::string name, std::string email,
            std::string phone, std::string address)
    : guestId(guestId), name(name), email(email), phone(phone), address(address) {}

std::string Guest::getGuestId() const { return guestId; }
std::string Guest::getName() const { return name; }
std::string Guest::getEmail() const { return email; }
std::string Guest::getPhone() const { return phone; }
std::string Guest::getAddress() const { return address; }

void Guest::displayInfo() const {
    std::cout << "Guest: " << name << " (ID: " << guestId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Address: " << address << std::endl;
} 