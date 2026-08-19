#ifndef PARKING_FEE_STRATEGY
#define PARKING_FEE_STRATEGY

#include "ParkingTicket.hpp"
#include <iostream>
using namespace std;
class FeeStrategy {
    private:
        int duration;
    public:
        virtual int  calculateFee(ParkingTicket* ticket) = 0;
        void setDuration(ParkingTicket* ticket);
        int getDuration();

};

#endif