#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>
#include <vector>
#include "Show.hpp"

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

class Booking {
private:
    std::string bookingId;
    Show* show;
    std::string customerName;
    std::string customerPhone;
    std::vector<int> seatNumbers;
    double totalAmount;
    BookingStatus status;
    std::string timestamp;

public:
    Booking(std::string bookingId, Show* show, std::string customerName,
           std::string customerPhone, const std::vector<int>& seatNumbers);
    
    std::string getBookingId() const;
    Show* getShow() const;
    std::string getCustomerName() const;
    std::string getCustomerPhone() const;
    const std::vector<int>& getSeatNumbers() const;
    double getTotalAmount() const;
    BookingStatus getStatus() const;
    std::string getTimestamp() const;
    
    void calculateTotalAmount();
    void setStatus(BookingStatus status);
    void displayInfo() const;
};

#endif 