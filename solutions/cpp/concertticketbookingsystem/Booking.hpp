#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include "Concert.hpp"

class Booking {
private:
    std::string bookingId;
    std::string customerName;
    Concert* concert;
    int seatNumber;
    double totalPrice;

public:
    Booking(std::string bookingId, std::string customerName, Concert* concert, 
            int seatNumber, double totalPrice);
    
    std::string getBookingId() const;
    std::string getCustomerName() const;
    Concert* getConcert() const;
    int getSeatNumber() const;
    double getTotalPrice() const;
    void displayInfo() const;
};

#endif 