#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include <vector>
#include "Seat.hpp"

class Flight {
private:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    int capacity;
    std::vector<Seat> seats;

public:
    Flight(std::string flightNumber, std::string origin, std::string destination, 
           std::string departureTime, int capacity);
    
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureTime() const;
    int getCapacity() const;
    std::vector<Seat>& getSeats();
    
    void displayFlightInfo() const;
    bool bookSeat(int seatNumber);
    bool cancelSeat(int seatNumber);
};

#endif 