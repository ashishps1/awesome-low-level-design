#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include "Guest.hpp"
#include "Room.hpp"

enum class BookingStatus {
    CONFIRMED,
    CHECKED_IN,
    CHECKED_OUT,
    CANCELLED
};

class Booking {
private:
    std::string bookingId;
    Guest* guest;
    Room* room;
    std::string checkInDate;
    std::string checkOutDate;
    int numberOfNights;
    double totalAmount;
    BookingStatus status;

public:
    Booking(std::string bookingId, Guest* guest, Room* room,
           std::string checkInDate, std::string checkOutDate, int numberOfNights);
    
    std::string getBookingId() const;
    Guest* getGuest() const;
    Room* getRoom() const;
    std::string getCheckInDate() const;
    std::string getCheckOutDate() const;
    int getNumberOfNights() const;
    double getTotalAmount() const;
    BookingStatus getStatus() const;
    
    void calculateTotalAmount();
    void setStatus(BookingStatus status);
    void displayInfo() const;
};

#endif 