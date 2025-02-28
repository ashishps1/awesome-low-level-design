#ifndef RENTAL_HPP
#define RENTAL_HPP

#include "Car.hpp"
#include "Customer.hpp"
#include <string>

class Rental {
private:
    std::string rentalId;
    Car* car;
    Customer* customer;
    std::string startDate;
    int days;
    double totalPrice;

public:
    Rental(std::string rentalId, Car* car, Customer* customer, 
           std::string startDate, int days);
    
    std::string getRentalId() const;
    Car* getCar() const;
    Customer* getCustomer() const;
    std::string getStartDate() const;
    int getDays() const;
    double getTotalPrice() const;
    
    void displayInfo() const;
};

#endif 