#include "ParkingTicket.hpp"
#include <iostream>
using namespace std;

ParkingTicket:: ParkingTicket(ParkingSpot* spot) : allottedSpot(spot), license(allottedSpot->getVehicle()->getLicensePlate()) {
    arrivalTime = chrono::duration_cast<std::chrono::seconds>(
                    chrono::system_clock::now().time_since_epoch()).count(); 
    ticketNum = ++id;
}

long long ParkingTicket::getEntryTime() {
    return arrivalTime;
}


void ParkingTicket::printTicket() {
    cout << "-------------------------------------\n" ;
    cout << "|     Ticket Number :             " << ticketNum << endl;
    cout << "|     SpotID        :             "  << allottedSpot->getSpotNumber() << endl;
    cout << "|     Vehicle Number  :         " << license << endl;
    cout << "-------------------------------------\n" ;
}
SpotType ParkingTicket::getSpotType () {
    return allottedSpot->getType();
}

int ParkingTicket:: id = 0;