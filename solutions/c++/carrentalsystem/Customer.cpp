#include "Customer.hpp"
#include <iostream>

Customer::Customer(std::string customerId, std::string name, std::string contactNumber)
    : customerId(customerId), name(name), contactNumber(contactNumber) {}

std::string Customer::getCustomerId() const { return customerId; }
std::string Customer::getName() const { return name; }
std::string Customer::getContactNumber() const { return contactNumber; }

void Customer::displayInfo() const {
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Contact Number: " << contactNumber << std::endl;
} 