#ifndef PARKING_FEE_FLAT
#define PARKING_FEE_FLAT

#include "FeeStrategy.hpp"

class FeeFlatRate: public FeeStrategy {
    private:
        int rate;
    public:
        int calculateFee(ParkingTicket* ticket) override;
        int getRate();
        void setRate();
};

#endif
