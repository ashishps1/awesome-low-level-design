#include "Rental.hpp"
#include <iostream>
#include <iomanip>

Rental::Rental(std::string rentalId, Car* car, Customer* customer, 
               std::string startDate, int days)
    : rentalId(rentalId), car(car), customer(customer), 
      startDate(startDate), days(days) {
    totalPrice = car->getBasePrice() * days;
}

std::string Rental::getRentalId() const { return rentalId; }
Car* Rental::getCar() const { return car; }
Customer* Rental::getCustomer() const { return customer; }
std::string Rental::getStartDate() const { return startDate; }
int Rental::getDays() const { return days; }
double Rental::getTotalPrice() const { return totalPrice; }

void Rental::displayInfo() const {
    std::cout << "\nRental Details:" << std::endl;
    std::cout << "Rental ID: " << rentalId << std::endl;
    std::cout << "Start Date: " << startDate << std::endl;
    std::cout << "Duration: " << days << " days" << std::endl;
    std::cout << "Total Price: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    std::cout << "\nCustomer Information:" << std::endl;
    customer->displayInfo();
    std::cout << "\nCar Information:" << std::endl;
    car->displayInfo();
} 