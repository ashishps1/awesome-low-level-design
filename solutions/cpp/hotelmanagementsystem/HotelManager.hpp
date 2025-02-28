#ifndef HOTEL_MANAGER_HPP
#define HOTEL_MANAGER_HPP

#include <vector>
#include <string>
#include "Room.hpp"
#include "Guest.hpp"
#include "Booking.hpp"

class HotelManager {
private:
    std::vector<Room*> rooms;
    std::vector<Guest*> guests;
    std::vector<Booking*> bookings;
    int bookingIdCounter;

public:
    HotelManager();
    ~HotelManager();
    
    void addRoom(Room* room);
    void addGuest(Guest* guest);
    
    Booking* createBooking(std::string guestId, std::string roomNumber,
                          std::string checkInDate, std::string checkOutDate,
                          int numberOfNights);
    
    bool checkIn(std::string bookingId);
    bool checkOut(std::string bookingId);
    bool cancelBooking(std::string bookingId);
    
    void displayAvailableRooms() const;
    void displayBookingHistory(std::string guestId) const;
    void displayAllGuests() const;
    void displayAllBookings() const;
    
private:
    Room* findRoom(const std::string& roomNumber) const;
    Guest* findGuest(const std::string& guestId) const;
    Booking* findBooking(const std::string& bookingId) const;
    std::string generateBookingId();
};

#endif 