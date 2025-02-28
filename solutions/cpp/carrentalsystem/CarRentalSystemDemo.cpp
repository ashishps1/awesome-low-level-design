#include "CarRentalSystem.hpp"
#include <iostream>

int main() {
    CarRentalSystem rentalSystem;
    
    // Add some cars
    Car* car1 = new Car("C001", "Toyota", "Camry", 60.0);
    Car* car2 = new Car("C002", "Honda", "Accord", 70.0);
    Car* car3 = new Car("C003", "BMW", "3 Series", 100.0);
    
    rentalSystem.addCar(car1);
    rentalSystem.addCar(car2);
    rentalSystem.addCar(car3);
    
    // Add some customers
    Customer* customer1 = new Customer("CUST001", "John Doe", "+1-555-0123");
    Customer* customer2 = new Customer("CUST002", "Jane Smith", "+1-555-0124");
    
    rentalSystem.addCustomer(customer1);
    rentalSystem.addCustomer(customer2);
    
    // Display available cars
    rentalSystem.displayAvailableCars();
    
    // Rent some cars
    std::string rental1 = rentalSystem.rentCar(car1, customer1, "2024-03-20", 3);
    std::string rental2 = rentalSystem.rentCar(car2, customer2, "2024-03-21", 5);
    
    if (!rental1.empty()) {
        std::cout << "\nRental created successfully: " << rental1 << std::endl;
    }
    if (!rental2.empty()) {
        std::cout << "Rental created successfully: " << rental2 << std::endl;
    }
    
    // Display all rentals
    rentalSystem.displayRentals();
    
    // Display available cars after rentals
    rentalSystem.displayAvailableCars();
    
    // Return a car
    if (rentalSystem.returnCar(rental1)) {
        std::cout << "\nCar returned successfully for rental: " << rental1 << std::endl;
    }
    
    // Display available cars after return
    rentalSystem.displayAvailableCars();
    
    return 0;
} 