#include "BookingSystem.hpp"
#include <iostream>
#include <algorithm>

BookingSystem::BookingSystem() : bookingIdCounter(1) {}

BookingSystem::~BookingSystem() {
    for (auto movie : movies) delete movie;
    for (auto theater : theaters) delete theater;
    for (auto booking : bookings) delete booking;
}

void BookingSystem::addMovie(Movie* movie) {
    movies.push_back(movie);
}

void BookingSystem::addTheater(Theater* theater) {
    theaters.push_back(theater);
}

Booking* BookingSystem::createBooking(std::string showId, std::string customerName,
                                    std::string customerPhone, const std::vector<int>& seats) {
    Show* show = findShow(showId);
    if (!show || show->getStatus() != ShowStatus::SCHEDULED) {
        return nullptr;
    }
    
    // Check if all seats are available
    for (int seatNumber : seats) {
        if (!show->isSeatAvailable(seatNumber)) {
            return nullptr;
        }
    }
    
    // Book all seats
    for (int seatNumber : seats) {
        show->bookSeat(seatNumber);
    }
    
    // Create booking
    Booking* booking = new Booking(generateBookingId(), show, customerName,
                                 customerPhone, seats);
    booking->setStatus(BookingStatus::CONFIRMED);
    bookings.push_back(booking);
    return booking;
}

bool BookingSystem::cancelBooking(std::string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() == BookingStatus::CANCELLED) {
        return false;
    }
    
    // Cancel seat bookings
    Show* show = booking->getShow();
    for (int seatNumber : booking->getSeatNumbers()) {
        show->cancelSeatBooking(seatNumber);
    }
    
    booking->setStatus(BookingStatus::CANCELLED);
    return true;
}

void BookingSystem::displayMovies() const {
    std::cout << "\nAvailable Movies:" << std::endl;
    for (const auto& movie : movies) {
        if (movie->isActive()) {
            movie->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void BookingSystem::displayTheaters() const {
    std::cout << "\nTheaters:" << std::endl;
    for (const auto& theater : theaters) {
        if (theater->isActive()) {
            theater->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void BookingSystem::displayShows(std::string movieId) const {
    std::cout << "\nShows for Movie ID " << movieId << ":" << std::endl;
    for (const auto& theater : theaters) {
        for (const auto& show : theater->getShows()) {
            if (show->getMovie()->getMovieId() == movieId) {
                show->displayInfo();
                std::cout << "------------------------" << std::endl;
            }
        }
    }
}

void BookingSystem::displayBooking(std::string bookingId) const {
    Booking* booking = findBooking(bookingId);
    if (booking) {
        booking->displayInfo();
    }
}

Show* BookingSystem::findShow(const std::string& showId) const {
    for (const auto& theater : theaters) {
        for (const auto& show : theater->getShows()) {
            if (show->getShowId() == showId) {
                return show;
            }
        }
    }
    return nullptr;
}

Booking* BookingSystem::findBooking(const std::string& bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) {
            return booking;
        }
    }
    return nullptr;
}

std::string BookingSystem::generateBookingId() {
    return "B" + std::to_string(bookingIdCounter++);
} 