#include "Booking.hpp"
#include <iostream>

Booking::Booking(std::string bookingId, Flight* flight, Passenger* passenger, int seatNumber)
    : bookingId(bookingId), flight(flight), passenger(passenger), seatNumber(seatNumber) {}

std::string Booking::getBookingId() const { return bookingId; }
Flight* Booking::getFlight() const { return flight; }
Passenger* Booking::getPassenger() const { return passenger; }
int Booking::getSeatNumber() const { return seatNumber; }

void Booking::displayBookingInfo() const {
    std::cout << "\nBooking Details:" << std::endl;
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Seat Number: " << seatNumber << std::endl;
    passenger->displayInfo();
    flight->displayFlightInfo();
} 