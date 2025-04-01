#include "Booking.hpp"
#include <iostream>
#include <iomanip>

Booking::Booking(std::string bookingId, std::string customerName, Concert* concert, 
                int seatNumber, double totalPrice)
    : bookingId(bookingId), customerName(customerName), concert(concert), 
      seatNumber(seatNumber), totalPrice(totalPrice) {}

std::string Booking::getBookingId() const { return bookingId; }
std::string Booking::getCustomerName() const { return customerName; }
Concert* Booking::getConcert() const { return concert; }
int Booking::getSeatNumber() const { return seatNumber; }
double Booking::getTotalPrice() const { return totalPrice; }

void Booking::displayInfo() const {
    std::cout << "\nBooking Details:" << std::endl;
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Customer Name: " << customerName << std::endl;
    std::cout << "Seat Number: " << seatNumber << std::endl;
    std::cout << "Total Price: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    std::cout << "\nConcert Information:" << std::endl;
    concert->displayInfo();
} 