#ifndef CAR_RENTAL_SYSTEM_HPP
#define CAR_RENTAL_SYSTEM_HPP

#include <vector>
#include <string>
#include "Car.hpp"
#include "Customer.hpp"
#include "Rental.hpp"

class CarRentalSystem {
private:
    std::vector<Car*> cars;
    std::vector<Customer*> customers;
    std::vector<Rental*> rentals;
    int rentalIdCounter;

public:
    CarRentalSystem();
    ~CarRentalSystem();
    
    void addCar(Car* car);
    void addCustomer(Customer* customer);
    std::string rentCar(Car* car, Customer* customer, std::string startDate, int days);
    bool returnCar(std::string rentalId);
    
    void displayAvailableCars() const;
    void displayRentals() const;
    void displayCustomers() const;
    
    Car* findCar(std::string carId) const;
    Customer* findCustomer(std::string customerId) const;
    Rental* findRental(std::string rentalId) const;
};

#endif 