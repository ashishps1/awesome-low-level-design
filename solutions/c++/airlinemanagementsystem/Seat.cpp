#include "Seat.hpp"

Seat::Seat(int number, bool isBooked) 
    : seatNumber(number), booked(isBooked) {}

int Seat::getSeatNumber() const { return seatNumber; }
bool Seat::isBooked() const { return booked; }
void Seat::book() { booked = true; }
void Seat::cancel() { booked = false; } 