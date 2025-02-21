#include "Booking.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

Booking::Booking(std::string bookingId, Show* show, std::string customerName,
                std::string customerPhone, const std::vector<int>& seatNumbers)
    : bookingId(bookingId), show(show), customerName(customerName),
      customerPhone(customerPhone), seatNumbers(seatNumbers),
      status(BookingStatus::PENDING) {
    // Get current timestamp
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = oss.str();
    
    calculateTotalAmount();
}

std::string Booking::getBookingId() const { return bookingId; }
Show* Booking::getShow() const { return show; }
std::string Booking::getCustomerName() const { return customerName; }
std::string Booking::getCustomerPhone() const { return customerPhone; }
const std::vector<int>& Booking::getSeatNumbers() const { return seatNumbers; }
double Booking::getTotalAmount() const { return totalAmount; }
BookingStatus Booking::getStatus() const { return status; }
std::string Booking::getTimestamp() const { return timestamp; }

void Booking::calculateTotalAmount() {
    totalAmount = show->getTicketPrice() * seatNumbers.size();
}

void Booking::setStatus(BookingStatus status) {
    this->status = status;
}

void Booking::displayInfo() const {
    std::cout << "\nBooking Details:" << std::endl;
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Customer Name: " << customerName << std::endl;
    std::cout << "Customer Phone: " << customerPhone << std::endl;
    show->displayInfo();
    std::cout << "Seats: ";
    for (int seat : seatNumbers) {
        std::cout << seat << " ";
    }
    std::cout << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) 
              << totalAmount << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case BookingStatus::PENDING: std::cout << "Pending"; break;
        case BookingStatus::CONFIRMED: std::cout << "Confirmed"; break;
        case BookingStatus::CANCELLED: std::cout << "Cancelled"; break;
    }
    std::cout << std::endl;
    std::cout << "Booking Time: " << timestamp << std::endl;
} 