#include "FeeStrategy.hpp"

void FeeStrategy::setDuration(ParkingTicket* ticket) {
    long long arrivalTime = ticket->getEntryTime();
    long long exitTime = chrono::duration_cast<std::chrono::seconds>(
                    chrono::system_clock::now().time_since_epoch()).count(); 

    duration  = exitTime - arrivalTime;
    
}

int FeeStrategy::getDuration() {
    return duration;
}
