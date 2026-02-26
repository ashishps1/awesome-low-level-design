#ifndef PARKING_FEE_VEHICLE_BASED
#define PARKING_FEE_VEHICLE_BASED

#include "FeeStrategy.hpp"

class FeeVehicleBased: public FeeStrategy {
    private:
        int rate;
    public:
        int calculateFee(ParkingTicket* ticket) override;
        int getRate();
        void setRate(ParkingTicket* ticket);
};

#endif
