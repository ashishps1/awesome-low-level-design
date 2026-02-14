#ifndef PARKING_TICKET_HPP
#define PARKING_TICKET_HPP

#include "ParkingSpot.hpp"
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

class ParkingTicket {
    private:
        ParkingSpot* allottedSpot;
        static int id;
        int ticketNum;
        long long arrivalTime;
        string license;

    public:
        ParkingTicket(ParkingSpot* spot); 
        void printTicket();
        SpotType getSpotType(); 

        // Will be used to calculate parking fee
        long long getEntryTime();
        
        
};

#endif