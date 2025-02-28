#include "ElevatorSystem.hpp"
#include <iostream>

ElevatorSystem::ElevatorSystem(int numElevators, int maxFloor, int minFloor)
    : maxFloor(maxFloor), minFloor(minFloor) {
    for (int i = 0; i < numElevators; i++) {
        elevators.push_back(new Elevator(i, maxFloor, minFloor));
    }
}

ElevatorSystem::~ElevatorSystem() {
    for (auto elevator : elevators) {
        delete elevator;
    }
}

void ElevatorSystem::addRequest(int elevatorId, const Request& request) {
    Elevator* elevator = findElevator(elevatorId);
    if (elevator) {
        elevator->addRequest(request);
        std::cout << "Added request to elevator " << elevatorId 
                  << " from floor " << request.getSourceFloor() 
                  << " to floor " << request.getDestinationFloor() << std::endl;
    }
}

void ElevatorSystem::step() {
    for (auto elevator : elevators) {
        if (elevator->getStatus() == Status::MOVING) {
            elevator->moveToNextFloor();
        }
        if (elevator->hasStopRequest()) {
            elevator->processFloor();
        }
    }
}

void ElevatorSystem::displayStatus() const {
    std::cout << "\nElevator System Status:" << std::endl;
    for (const auto& elevator : elevators) {
        elevator->displayInfo();
    }
    std::cout << std::endl;
}

Elevator* ElevatorSystem::findElevator(int elevatorId) const {
    if (elevatorId >= 0 && elevatorId < elevators.size()) {
        return elevators[elevatorId];
    }
    return nullptr;
} 