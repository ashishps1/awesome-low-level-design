#ifndef SEAT_HPP
#define SEAT_HPP

class Seat {
private:
    int seatNumber;
    bool booked;

public:
    Seat(int number, bool isBooked = false);
    
    int getSeatNumber() const;
    bool isBooked() const;
    void book();
    void cancel();
};

#endif 