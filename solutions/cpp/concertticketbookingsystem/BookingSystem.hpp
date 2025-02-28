#ifndef BOOKING_SYSTEM_HPP
#define BOOKING_SYSTEM_HPP

#include <vector>
#include <string>
#include "Concert.hpp"
#include "Booking.hpp"

class BookingSystem {
private:
    std::vector<Concert*> concerts;
    std::vector<Booking*> bookings;
    int bookingIdCounter;

public:
    BookingSystem();
    ~BookingSystem();
    
    void addConcert(Concert* concert);
    std::string createBooking(std::string customerName, Concert* concert, int seatNumber);
    bool cancelBooking(std::string bookingId);
    
    void displayAllConcerts() const;
    void displayAllBookings() const;
    void displayAvailableSeats(Concert* concert) const;
    
    Concert* findConcert(std::string concertId) const;
    Booking* findBooking(std::string bookingId) const;
};

#endif 