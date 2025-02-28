#include "Passenger.hpp"
#include <iostream>

Passenger::Passenger(std::string name, std::string passportNumber, std::string contactNumber)
    : name(name), passportNumber(passportNumber), contactNumber(contactNumber) {}

std::string Passenger::getName() const { return name; }
std::string Passenger::getPassportNumber() const { return passportNumber; }
std::string Passenger::getContactNumber() const { return contactNumber; }

void Passenger::displayInfo() const {
    std::cout << "Passenger Details:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Passport Number: " << passportNumber << std::endl;
    std::cout << "Contact Number: " << contactNumber << std::endl;
} 