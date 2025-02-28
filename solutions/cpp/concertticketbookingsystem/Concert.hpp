#ifndef CONCERT_HPP
#define CONCERT_HPP

#include <string>
#include <vector>
#include "Seat.hpp"

class Concert {
private:
    std::string concertId;
    std::string name;
    std::string venue;
    std::string date;
    double basePrice;
    std::vector<Seat> seats;
    int totalSeats;

public:
    Concert(std::string concertId, std::string name, std::string venue, 
            std::string date, double basePrice, int totalSeats);
    
    std::string getConcertId() const;
    std::string getName() const;
    std::string getVenue() const;
    std::string getDate() const;
    double getBasePrice() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;
    
    bool bookSeat(int seatNumber);
    bool cancelSeat(int seatNumber);
    bool isSeatAvailable(int seatNumber) const;
    void displayInfo() const;
};

#endif 