#include "HotelManager.hpp"
#include <iostream>

int main() {
    HotelManager hotel;
    
    // Add rooms
    Room* room1 = new Room("101", RoomType::STANDARD, 100.0, 2);
    Room* room2 = new Room("201", RoomType::DELUXE, 150.0, 3);
    Room* room3 = new Room("301", RoomType::SUITE, 250.0, 4);
    
    hotel.addRoom(room1);
    hotel.addRoom(room2);
    hotel.addRoom(room3);
    
    // Add guests
    Guest* guest1 = new Guest("G001", "John Doe", "john@example.com",
                            "+1-555-0123", "123 Main St");
    hotel.addGuest(guest1);
    
    // Display available rooms
    hotel.displayAvailableRooms();
    
    // Create a booking
    Booking* booking = hotel.createBooking("G001", "101", "2024-01-01",
                                         "2024-01-03", 2);
    if (booking) {
        std::cout << "\nBooking created successfully!" << std::endl;
        booking->displayInfo();
        
        // Check in
        if (hotel.checkIn(booking->getBookingId())) {
            std::cout << "\nChecked in successfully!" << std::endl;
        }
        
        // Display available rooms after check-in
        hotel.displayAvailableRooms();
        
        // Check out
        if (hotel.checkOut(booking->getBookingId())) {
            std::cout << "\nChecked out successfully!" << std::endl;
        }
        
        // Display booking history
        hotel.displayBookingHistory("G001");
    }
    
    return 0;
} 