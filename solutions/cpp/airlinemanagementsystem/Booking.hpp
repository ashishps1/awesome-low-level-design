#ifndef BOOKING_HPP
#define BOOKING_HPP

#include "Flight.hpp"
#include "Passenger.hpp"
#include <string>

class Booking {
private:
    std::string bookingId;
    Flight* flight;
    Passenger* passenger;
    int seatNumber;

public:
    Booking(std::string bookingId, Flight* flight, Passenger* passenger, int seatNumber);
    
    std::string getBookingId() const;
    Flight* getFlight() const;
    Passenger* getPassenger() const;
    int getSeatNumber() const;
    void displayBookingInfo() const;
};

#endif 