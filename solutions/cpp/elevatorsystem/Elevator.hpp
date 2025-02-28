#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <vector>
#include <queue>
#include <string>
#include "Request.hpp"

enum class Direction {
    UP,
    DOWN,
    IDLE
};

enum class Status {
    MOVING,
    STOPPED,
    MAINTENANCE
};

class Elevator {
private:
    int id;
    int currentFloor;
    Direction direction;
    Status status;
    int maxFloor;
    int minFloor;
    std::vector<bool> floorsToVisit;
    std::queue<Request> requests;

public:
    Elevator(int id, int maxFloor, int minFloor = 0);
    
    int getId() const;
    int getCurrentFloor() const;
    Direction getDirection() const;
    Status getStatus() const;
    
    void setDirection(Direction direction);
    void setStatus(Status status);
    
    void addRequest(const Request& request);
    void moveToNextFloor();
    bool hasStopRequest() const;
    void processFloor();
    void displayInfo() const;
    
private:
    void updateDirection();
};

#endif 