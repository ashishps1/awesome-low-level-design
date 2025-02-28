#include "Elevator.hpp"
#include <iostream>

Elevator::Elevator(int id, int maxFloor, int minFloor)
    : id(id), currentFloor(minFloor), direction(Direction::IDLE),
      status(Status::STOPPED), maxFloor(maxFloor), minFloor(minFloor) {
    floorsToVisit.resize(maxFloor + 1, false);
}

int Elevator::getId() const { return id; }
int Elevator::getCurrentFloor() const { return currentFloor; }
Direction Elevator::getDirection() const { return direction; }
Status Elevator::getStatus() const { return status; }

void Elevator::setDirection(Direction direction) {
    this->direction = direction;
}

void Elevator::setStatus(Status status) {
    this->status = status;
}

void Elevator::addRequest(const Request& request) {
    requests.push(request);
    floorsToVisit[request.getDestinationFloor()] = true;
    
    if (direction == Direction::IDLE) {
        if (request.getDestinationFloor() > currentFloor) {
            direction = Direction::UP;
        } else if (request.getDestinationFloor() < currentFloor) {
            direction = Direction::DOWN;
        }
    }
}

void Elevator::moveToNextFloor() {
    if (status != Status::MOVING) return;
    
    if (direction == Direction::UP && currentFloor < maxFloor) {
        currentFloor++;
    } else if (direction == Direction::DOWN && currentFloor > minFloor) {
        currentFloor--;
    }
    
    updateDirection();
}

bool Elevator::hasStopRequest() const {
    return floorsToVisit[currentFloor];
}

void Elevator::processFloor() {
    if (floorsToVisit[currentFloor]) {
        floorsToVisit[currentFloor] = false;
        status = Status::STOPPED;
        std::cout << "Elevator " << id << " stopped at floor " << currentFloor << std::endl;
        
        // Remove processed requests
        while (!requests.empty() && requests.front().getDestinationFloor() == currentFloor) {
            requests.pop();
        }
    }
}

void Elevator::updateDirection() {
    if (direction == Direction::UP) {
        bool hasHigherFloorRequest = false;
        for (int i = currentFloor + 1; i <= maxFloor; i++) {
            if (floorsToVisit[i]) {
                hasHigherFloorRequest = true;
                break;
            }
        }
        if (!hasHigherFloorRequest) {
            direction = Direction::DOWN;
        }
    } else if (direction == Direction::DOWN) {
        bool hasLowerFloorRequest = false;
        for (int i = currentFloor - 1; i >= minFloor; i--) {
            if (floorsToVisit[i]) {
                hasLowerFloorRequest = true;
                break;
            }
        }
        if (!hasLowerFloorRequest) {
            direction = Direction::UP;
        }
    }
    
    if (!requests.empty()) {
        status = Status::MOVING;
    } else {
        direction = Direction::IDLE;
        status = Status::STOPPED;
    }
}

void Elevator::displayInfo() const {
    std::cout << "Elevator " << id << " - Floor: " << currentFloor;
    std::cout << " - Direction: ";
    switch (direction) {
        case Direction::UP: std::cout << "UP"; break;
        case Direction::DOWN: std::cout << "DOWN"; break;
        case Direction::IDLE: std::cout << "IDLE"; break;
    }
    std::cout << " - Status: ";
    switch (status) {
        case Status::MOVING: std::cout << "MOVING"; break;
        case Status::STOPPED: std::cout << "STOPPED"; break;
        case Status::MAINTENANCE: std::cout << "MAINTENANCE"; break;
    }
    std::cout << std::endl;
} 