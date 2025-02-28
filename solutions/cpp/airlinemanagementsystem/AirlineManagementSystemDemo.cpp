#include "AirlineManagementSystem.hpp"
#include <iostream>

int main() {
    AirlineManagementSystem ams;
    
    // Create flights
    Flight* flight1 = new Flight("FL001", "New York", "London", "2024-03-20 10:00", 100);
    Flight* flight2 = new Flight("FL002", "London", "Paris", "2024-03-21 15:30", 80);
    ams.addFlight(flight1);
    ams.addFlight(flight2);
    
    // Create passengers
    Passenger* passenger1 = new Passenger("John Doe", "P123456", "+1-555-0123");
    Passenger* passenger2 = new Passenger("Jane Smith", "P789012", "+1-555-0124");
    ams.addPassenger(passenger1);
    ams.addPassenger(passenger2);
    
    // Display all flights and passengers
    ams.displayAllFlights();
    ams.displayAllPassengers();
    
    // Create bookings
    std::string booking1 = ams.createBooking(flight1, passenger1, 1);
    std::string booking2 = ams.createBooking(flight2, passenger2, 1);
    
    if (!booking1.empty()) {
        std::cout << "\nBooking created successfully: " << booking1 << std::endl;
    }
    if (!booking2.empty()) {
        std::cout << "Booking created successfully: " << booking2 << std::endl;
    }
    
    // Display all bookings
    ams.displayAllBookings();
    
    // Cancel a booking
    if (ams.cancelBooking(booking1)) {
        std::cout << "\nBooking " << booking1 << " cancelled successfully" << std::endl;
    }
    
    // Display updated bookings
    ams.displayAllBookings();
    
    return 0;
} 