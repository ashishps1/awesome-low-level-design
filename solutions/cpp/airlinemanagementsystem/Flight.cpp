#include "Flight.hpp"
#include <iostream>

Flight::Flight(std::string flightNumber, std::string origin, std::string destination, 
               std::string departureTime, int capacity) 
    : flightNumber(flightNumber), origin(origin), destination(destination),
      departureTime(departureTime), capacity(capacity) {
    
    // Initialize seats
    for (int i = 1; i <= capacity; i++) {
        seats.push_back(Seat(i, false));
    }
}

std::string Flight::getFlightNumber() const { return flightNumber; }
std::string Flight::getOrigin() const { return origin; }
std::string Flight::getDestination() const { return destination; }
std::string Flight::getDepartureTime() const { return departureTime; }
int Flight::getCapacity() const { return capacity; }
std::vector<Seat>& Flight::getSeats() { return seats; }

void Flight::displayFlightInfo() const {
    std::cout << "Flight " << flightNumber << std::endl;
    std::cout << "From: " << origin << " To: " << destination << std::endl;
    std::cout << "Departure Time: " << departureTime << std::endl;
    std::cout << "Capacity: " << capacity << " seats" << std::endl;
}

bool Flight::bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > capacity) return false;
    if (seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].book();
    return true;
}

bool Flight::cancelSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > capacity) return false;
    if (!seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].cancel();
    return true;
} 