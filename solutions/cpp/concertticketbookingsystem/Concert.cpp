#include "Concert.hpp"
#include <iostream>
#include <iomanip>

Concert::Concert(std::string concertId, std::string name, std::string venue, 
                std::string date, double basePrice, int totalSeats)
    : concertId(concertId), name(name), venue(venue), date(date), 
      basePrice(basePrice), totalSeats(totalSeats) {
    
    // Initialize seats
    for (int i = 1; i <= totalSeats; i++) {
        seats.push_back(Seat(i));
    }
}

std::string Concert::getConcertId() const { return concertId; }
std::string Concert::getName() const { return name; }
std::string Concert::getVenue() const { return venue; }
std::string Concert::getDate() const { return date; }
double Concert::getBasePrice() const { return basePrice; }
int Concert::getTotalSeats() const { return totalSeats; }

int Concert::getAvailableSeats() const {
    int available = 0;
    for (const auto& seat : seats) {
        if (!seat.isBooked()) available++;
    }
    return available;
}

bool Concert::bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    if (seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].book();
    return true;
}

bool Concert::cancelSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    if (!seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].cancel();
    return true;
}

bool Concert::isSeatAvailable(int seatNumber) const {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    return !seats[seatNumber - 1].isBooked();
}

void Concert::displayInfo() const {
    std::cout << "Concert: " << name << std::endl;
    std::cout << "ID: " << concertId << std::endl;
    std::cout << "Venue: " << venue << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << basePrice << std::endl;
    std::cout << "Available Seats: " << getAvailableSeats() << "/" << totalSeats << std::endl;
} 