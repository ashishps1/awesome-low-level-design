
#include "FeeVehicleBased.hpp"
#include "Vehicle.hpp"

int FeeVehicleBased:: calculateFee(ParkingTicket* ticket) {
    setDuration(ticket);
    setRate(ticket);
    return rate * getDuration();
        
}

void FeeVehicleBased::setRate(ParkingTicket* ticket) {
    SpotType type = ticket->getSpotType();  // get spot type to set rate;

    switch (type) {
        case SpotType::COMPACT :
            rate = 3;
            break;

        case SpotType::REGULAR:
            rate = 4;
            break;

        case SpotType::LARGE:
            rate = 5;
    }
}