#include "Seat.hpp"

Seat::Seat(int number) : seatNumber(number), booked(false) {}

int Seat::getSeatNumber() const { return seatNumber; }
bool Seat::isBooked() const { return booked; }
void Seat::book() { booked = true; }
void Seat::cancel() { booked = false; } 