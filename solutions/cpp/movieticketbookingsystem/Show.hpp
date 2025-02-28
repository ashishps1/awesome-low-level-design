#ifndef SHOW_HPP
#define SHOW_HPP

#include <string>
#include <vector>
#include "Movie.hpp"

enum class ShowStatus {
    SCHEDULED,
    RUNNING,
    COMPLETED,
    CANCELLED
};

class Show {
private:
    std::string showId;
    Movie* movie;
    std::string date;
    std::string startTime;
    double ticketPrice;
    std::vector<bool> seats;  // true if seat is booked
    ShowStatus status;

public:
    Show(std::string showId, Movie* movie, std::string date,
         std::string startTime, double ticketPrice, int totalSeats);
    
    std::string getShowId() const;
    Movie* getMovie() const;
    std::string getDate() const;
    std::string getStartTime() const;
    double getTicketPrice() const;
    ShowStatus getStatus() const;
    
    bool isSeatAvailable(int seatNumber) const;
    bool bookSeat(int seatNumber);
    void cancelSeatBooking(int seatNumber);
    void setStatus(ShowStatus status);
    int getAvailableSeats() const;
    void displayInfo() const;
};

#endif 