#include "CarRentalSystem.hpp"
#include <iostream>
#include <algorithm>

CarRentalSystem::CarRentalSystem() : rentalIdCounter(1) {}

CarRentalSystem::~CarRentalSystem() {
    for (auto car : cars) delete car;
    for (auto customer : customers) delete customer;
    for (auto rental : rentals) delete rental;
}

void CarRentalSystem::addCar(Car* car) {
    cars.push_back(car);
}

void CarRentalSystem::addCustomer(Customer* customer) {
    customers.push_back(customer);
}

std::string CarRentalSystem::rentCar(Car* car, Customer* customer, 
                                   std::string startDate, int days) {
    if (!car->isAvailable()) return "";
    
    std::string rentalId = "R" + std::to_string(rentalIdCounter++);
    Rental* rental = new Rental(rentalId, car, customer, startDate, days);
    rentals.push_back(rental);
    car->setAvailable(false);
    return rentalId;
}

bool CarRentalSystem::returnCar(std::string rentalId) {
    Rental* rental = findRental(rentalId);
    if (!rental) return false;
    
    rental->getCar()->setAvailable(true);
    
    auto it = std::find(rentals.begin(), rentals.end(), rental);
    if (it != rentals.end()) {
        rentals.erase(it);
        delete rental;
        return true;
    }
    return false;
}

void CarRentalSystem::displayAvailableCars() const {
    std::cout << "\nAvailable Cars:" << std::endl;
    for (const auto& car : cars) {
        if (car->isAvailable()) {
            car->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void CarRentalSystem::displayRentals() const {
    std::cout << "\nCurrent Rentals:" << std::endl;
    for (const auto& rental : rentals) {
        rental->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void CarRentalSystem::displayCustomers() const {
    std::cout << "\nRegistered Customers:" << std::endl;
    for (const auto& customer : customers) {
        customer->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

Car* CarRentalSystem::findCar(std::string carId) const {
    for (auto car : cars) {
        if (car->getCarId() == carId) return car;
    }
    return nullptr;
}

Customer* CarRentalSystem::findCustomer(std::string customerId) const {
    for (auto customer : customers) {
        if (customer->getCustomerId() == customerId) return customer;
    }
    return nullptr;
}

Rental* CarRentalSystem::findRental(std::string rentalId) const {
    for (auto rental : rentals) {
        if (rental->getRentalId() == rentalId) return rental;
    }
    return nullptr;
} 