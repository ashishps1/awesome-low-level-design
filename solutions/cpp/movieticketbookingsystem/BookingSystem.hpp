#ifndef BOOKING_SYSTEM_HPP
#define BOOKING_SYSTEM_HPP

#include <vector>
#include <string>
#include "Movie.hpp"
#include "Theater.hpp"
#include "Show.hpp"
#include "Booking.hpp"

class BookingSystem {
private:
    std::vector<Movie*> movies;
    std::vector<Theater*> theaters;
    std::vector<Booking*> bookings;
    int bookingIdCounter;

public:
    BookingSystem();
    ~BookingSystem();
    
    void addMovie(Movie* movie);
    void addTheater(Theater* theater);
    
    Booking* createBooking(std::string showId, std::string customerName,
                          std::string customerPhone, const std::vector<int>& seats);
    bool cancelBooking(std::string bookingId);
    
    void displayMovies() const;
    void displayTheaters() const;
    void displayShows(std::string movieId) const;
    void displayBooking(std::string bookingId) const;
    
private:
    Show* findShow(const std::string& showId) const;
    Booking* findBooking(const std::string& bookingId) const;
    std::string generateBookingId();
};

#endif 