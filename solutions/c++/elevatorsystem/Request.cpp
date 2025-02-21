#include "Request.hpp"

Request::Request(int sourceFloor, int destinationFloor)
    : sourceFloor(sourceFloor), destinationFloor(destinationFloor) {
    isUp = destinationFloor > sourceFloor;
}

int Request::getSourceFloor() const { return sourceFloor; }
int Request::getDestinationFloor() const { return destinationFloor; }
bool Request::getIsUp() const { return isUp; } 