#include "Booking.hpp"
#include <iostream>
#include <iomanip>

Booking::Booking(std::string bookingId, Guest* guest, Room* room,
                std::string checkInDate, std::string checkOutDate, int numberOfNights)
    : bookingId(bookingId), guest(guest), room(room),
      checkInDate(checkInDate), checkOutDate(checkOutDate),
      numberOfNights(numberOfNights), status(BookingStatus::CONFIRMED) {
    calculateTotalAmount();
}

std::string Booking::getBookingId() const { return bookingId; }
Guest* Booking::getGuest() const { return guest; }
Room* Booking::getRoom() const { return room; }
std::string Booking::getCheckInDate() const { return checkInDate; }
std::string Booking::getCheckOutDate() const { return checkOutDate; }
int Booking::getNumberOfNights() const { return numberOfNights; }
double Booking::getTotalAmount() const { return totalAmount; }
BookingStatus Booking::getStatus() const { return status; }

void Booking::calculateTotalAmount() {
    totalAmount = room->getPricePerNight() * numberOfNights;
}

void Booking::setStatus(BookingStatus status) {
    this->status = status;
}

void Booking::displayInfo() const {
    std::cout << "\nBooking Details:" << std::endl;
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Guest: " << guest->getName() << std::endl;
    std::cout << "Room: " << room->getRoomNumber() << std::endl;
    std::cout << "Check-in Date: " << checkInDate << std::endl;
    std::cout << "Check-out Date: " << checkOutDate << std::endl;
    std::cout << "Number of Nights: " << numberOfNights << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) 
              << totalAmount << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case BookingStatus::CONFIRMED: std::cout << "Confirmed"; break;
        case BookingStatus::CHECKED_IN: std::cout << "Checked In"; break;
        case BookingStatus::CHECKED_OUT: std::cout << "Checked Out"; break;
        case BookingStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
} 