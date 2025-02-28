#include "BookingSystem.hpp"
#include <iostream>

int main() {
    BookingSystem bookingSystem;
    
    // Create some concerts
    Concert* concert1 = new Concert("C001", "Rock Festival", "Stadium A", "2024-07-15", 100.0, 50);
    Concert* concert2 = new Concert("C002", "Jazz Night", "Hall B", "2024-07-20", 75.0, 30);
    
    bookingSystem.addConcert(concert1);
    bookingSystem.addConcert(concert2);
    
    // Display all concerts
    bookingSystem.displayAllConcerts();
    
    // Make some bookings
    std::string booking1 = bookingSystem.createBooking("John Doe", concert1, 1);
    std::string booking2 = bookingSystem.createBooking("Jane Smith", concert1, 2);
    std::string booking3 = bookingSystem.createBooking("Alice Johnson", concert2, 1);
    
    if (!booking1.empty()) {
        std::cout << "\nBooking created successfully: " << booking1 << std::endl;
    }
    if (!booking2.empty()) {
        std::cout << "Booking created successfully: " << booking2 << std::endl;
    }
    if (!booking3.empty()) {
        std::cout << "Booking created successfully: " << booking3 << std::endl;
    }
    
    // Display all bookings
    bookingSystem.displayAllBookings();
    
    // Display available seats for concert1
    bookingSystem.displayAvailableSeats(concert1);
    
    // Cancel a booking
    if (bookingSystem.cancelBooking(booking1)) {
        std::cout << "\nBooking " << booking1 << " cancelled successfully" << std::endl;
    }
    
    // Display updated available seats
    bookingSystem.displayAvailableSeats(concert1);
    
    return 0;
} 