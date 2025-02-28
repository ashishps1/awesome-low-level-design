#include "Show.hpp"
#include <iostream>
#include <iomanip>

Show::Show(std::string showId, Movie* movie, std::string date,
           std::string startTime, double ticketPrice, int totalSeats)
    : showId(showId), movie(movie), date(date), startTime(startTime),
      ticketPrice(ticketPrice), seats(totalSeats, false),
      status(ShowStatus::SCHEDULED) {}

std::string Show::getShowId() const { return showId; }
Movie* Show::getMovie() const { return movie; }
std::string Show::getDate() const { return date; }
std::string Show::getStartTime() const { return startTime; }
double Show::getTicketPrice() const { return ticketPrice; }
ShowStatus Show::getStatus() const { return status; }

bool Show::isSeatAvailable(int seatNumber) const {
    if (seatNumber < 1 || seatNumber > seats.size()) return false;
    return !seats[seatNumber - 1];
}

bool Show::bookSeat(int seatNumber) {
    if (!isSeatAvailable(seatNumber)) return false;
    seats[seatNumber - 1] = true;
    return true;
}

void Show::cancelSeatBooking(int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= seats.size()) {
        seats[seatNumber - 1] = false;
    }
}

void Show::setStatus(ShowStatus status) {
    this->status = status;
}

int Show::getAvailableSeats() const {
    int count = 0;
    for (bool seat : seats) {
        if (!seat) count++;
    }
    return count;
}

void Show::displayInfo() const {
    std::cout << "\nShow Details:" << std::endl;
    std::cout << "Show ID: " << showId << std::endl;
    movie->displayInfo();
    std::cout << "Date: " << date << std::endl;
    std::cout << "Start Time: " << startTime << std::endl;
    std::cout << "Ticket Price: $" << std::fixed << std::setprecision(2) 
              << ticketPrice << std::endl;
    std::cout << "Available Seats: " << getAvailableSeats() 
              << "/" << seats.size() << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case ShowStatus::SCHEDULED: std::cout << "Scheduled"; break;
        case ShowStatus::RUNNING: std::cout << "Running"; break;
        case ShowStatus::COMPLETED: std::cout << "Completed"; break;
        case ShowStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
} 