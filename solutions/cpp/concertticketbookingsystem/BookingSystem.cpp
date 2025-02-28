#include "BookingSystem.hpp"
#include <iostream>
#include <algorithm>

BookingSystem::BookingSystem() : bookingIdCounter(1) {}

BookingSystem::~BookingSystem() {
    for (auto concert : concerts) delete concert;
    for (auto booking : bookings) delete booking;
}

void BookingSystem::addConcert(Concert* concert) {
    concerts.push_back(concert);
}

std::string BookingSystem::createBooking(std::string customerName, Concert* concert, int seatNumber) {
    if (!concert->bookSeat(seatNumber)) {
        std::cout << "Failed to book seat: Seat " << seatNumber << " is not available" << std::endl;
        return "";
    }
    
    std::string bookingId = "B" + std::to_string(bookingIdCounter++);
    double totalPrice = concert->getBasePrice();  // Could add premium pricing logic here
    
    Booking* booking = new Booking(bookingId, customerName, concert, seatNumber, totalPrice);
    bookings.push_back(booking);
    return bookingId;
}

bool BookingSystem::cancelBooking(std::string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking) return false;
    
    booking->getConcert()->cancelSeat(booking->getSeatNumber());
    
    auto it = std::find(bookings.begin(), bookings.end(), booking);
    if (it != bookings.end()) {
        bookings.erase(it);
        delete booking;
        return true;
    }
    return false;
}

void BookingSystem::displayAllConcerts() const {
    std::cout << "\nAvailable Concerts:" << std::endl;
    for (const auto& concert : concerts) {
        concert->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void BookingSystem::displayAllBookings() const {
    std::cout << "\nCurrent Bookings:" << std::endl;
    for (const auto& booking : bookings) {
        booking->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void BookingSystem::displayAvailableSeats(Concert* concert) const {
    std::cout << "\nAvailable seats for concert " << concert->getName() << ":" << std::endl;
    for (int i = 1; i <= concert->getTotalSeats(); i++) {
        if (concert->isSeatAvailable(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

Concert* BookingSystem::findConcert(std::string concertId) const {
    for (auto concert : concerts) {
        if (concert->getConcertId() == concertId) return concert;
    }
    return nullptr;
}

Booking* BookingSystem::findBooking(std::string bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) return booking;
    }
    return nullptr;
} 