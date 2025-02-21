#ifndef ELEVATOR_SYSTEM_HPP
#define ELEVATOR_SYSTEM_HPP

#include <vector>
#include "Elevator.hpp"

class ElevatorSystem {
private:
    std::vector<Elevator*> elevators;
    int maxFloor;
    int minFloor;

public:
    ElevatorSystem(int numElevators, int maxFloor, int minFloor = 0);
    ~ElevatorSystem();
    
    void addRequest(int elevatorId, const Request& request);
    void step();
    void displayStatus() const;
    
private:
    Elevator* findElevator(int elevatorId) const;
};

#endif 