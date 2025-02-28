#include "HotelManager.hpp"
#include <iostream>

HotelManager::HotelManager() : bookingIdCounter(1) {}

HotelManager::~HotelManager() {
    for (auto room : rooms) delete room;
    for (auto guest : guests) delete guest;
    for (auto booking : bookings) delete booking;
}

void HotelManager::addRoom(Room* room) {
    rooms.push_back(room);
}

void HotelManager::addGuest(Guest* guest) {
    guests.push_back(guest);
}

Booking* HotelManager::createBooking(std::string guestId, std::string roomNumber,
                                   std::string checkInDate, std::string checkOutDate,
                                   int numberOfNights) {
    Guest* guest = findGuest(guestId);
    Room* room = findRoom(roomNumber);
    
    if (!guest || !room || room->getStatus() != RoomStatus::AVAILABLE) {
        return nullptr;
    }
    
    Booking* booking = new Booking(generateBookingId(), guest, room,
                                 checkInDate, checkOutDate, numberOfNights);
    bookings.push_back(booking);
    return booking;
}

bool HotelManager::checkIn(std::string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CONFIRMED) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CHECKED_IN);
    booking->getRoom()->setStatus(RoomStatus::OCCUPIED);
    return true;
}

bool HotelManager::checkOut(std::string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CHECKED_IN) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CHECKED_OUT);
    booking->getRoom()->setStatus(RoomStatus::AVAILABLE);
    return true;
}

bool HotelManager::cancelBooking(std::string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CONFIRMED) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CANCELLED);
    booking->getRoom()->setStatus(RoomStatus::AVAILABLE);
    return true;
}

void HotelManager::displayAvailableRooms() const {
    std::cout << "\nAvailable Rooms:" << std::endl;
    for (const auto& room : rooms) {
        if (room->getStatus() == RoomStatus::AVAILABLE) {
            room->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void HotelManager::displayBookingHistory(std::string guestId) const {
    std::cout << "\nBooking History:" << std::endl;
    for (const auto& booking : bookings) {
        if (booking->getGuest()->getGuestId() == guestId) {
            booking->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void HotelManager::displayAllGuests() const {
    std::cout << "\nAll Guests:" << std::endl;
    for (const auto& guest : guests) {
        guest->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void HotelManager::displayAllBookings() const {
    std::cout << "\nAll Bookings:" << std::endl;
    for (const auto& booking : bookings) {
        booking->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

Room* HotelManager::findRoom(const std::string& roomNumber) const {
    for (auto room : rooms) {
        if (room->getRoomNumber() == roomNumber) return room;
    }
    return nullptr;
}

Guest* HotelManager::findGuest(const std::string& guestId) const {
    for (auto guest : guests) {
        if (guest->getGuestId() == guestId) return guest;
    }
    return nullptr;
}

Booking* HotelManager::findBooking(const std::string& bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) return booking;
    }
    return nullptr;
}

std::string HotelManager::generateBookingId() {
    return "BK" + std::to_string(bookingIdCounter++);
} 