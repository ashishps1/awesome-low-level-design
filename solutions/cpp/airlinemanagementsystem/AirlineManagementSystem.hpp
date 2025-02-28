#ifndef AIRLINE_MANAGEMENT_SYSTEM_HPP
#define AIRLINE_MANAGEMENT_SYSTEM_HPP

#include <vector>
#include <string>
#include "Flight.hpp"
#include "Passenger.hpp"
#include "Booking.hpp"

class AirlineManagementSystem {
private:
    std::vector<Flight*> flights;
    std::vector<Passenger*> passengers;
    std::vector<Booking*> bookings;
    int bookingIdCounter;

public:
    AirlineManagementSystem();
    ~AirlineManagementSystem();
    
    void addFlight(Flight* flight);
    void addPassenger(Passenger* passenger);
    std::string createBooking(Flight* flight, Passenger* passenger, int seatNumber);
    bool cancelBooking(std::string bookingId);
    
    void displayAllFlights() const;
    void displayAllPassengers() const;
    void displayAllBookings() const;
    
    Flight* findFlight(std::string flightNumber) const;
    Passenger* findPassenger(std::string passportNumber) const;
    Booking* findBooking(std::string bookingId) const;
};

#endif 