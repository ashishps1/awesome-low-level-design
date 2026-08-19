#include "FeeFlatRate.hpp"
//Default rate is Rs 2 per second

int FeeFlatRate::calculateFee(ParkingTicket* ticket) {
    setDuration(ticket);
    setRate();
    return rate * getDuration();
}

int FeeFlatRate::getRate() {
    return rate;
}

void FeeFlatRate::setRate() {
    rate = 2;
}