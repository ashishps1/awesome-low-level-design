// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Request;
class Elevator;
class ElevatorSystem;

// ===== Request.hpp =====
class Request {
private:
    int sourceFloor;
    int destinationFloor;
    bool isUp;

public:
    Request(int sourceFloor, int destinationFloor);
    
    int getSourceFloor() const;
    int getDestinationFloor() const;
    bool getIsUp() const;
};

// ===== Elevator.hpp =====
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
    vector<bool> floorsToVisit;
    queue<Request> requests;

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

// ===== ElevatorSystem.hpp =====
class ElevatorSystem {
private:
    vector<Elevator*> elevators;
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

// ===== Elevator.cpp =====
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
        cout << "Elevator " << id << " stopped at floor " << currentFloor << endl;
        
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
    cout << "Elevator " << id << " - Floor: " << currentFloor;
    cout << " - Direction: ";
    switch (direction) {
        case Direction::UP: cout << "UP"; break;
        case Direction::DOWN: cout << "DOWN"; break;
        case Direction::IDLE: cout << "IDLE"; break;
    }
    cout << " - Status: ";
    switch (status) {
        case Status::MOVING: cout << "MOVING"; break;
        case Status::STOPPED: cout << "STOPPED"; break;
        case Status::MAINTENANCE: cout << "MAINTENANCE"; break;
    }
    cout << endl;
} 

// ===== ElevatorSystem.cpp =====
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
        cout << "Added request to elevator " << elevatorId 
                  << " from floor " << request.getSourceFloor() 
                  << " to floor " << request.getDestinationFloor() << endl;
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
    cout << "\nElevator System Status:" << endl;
    for (const auto& elevator : elevators) {
        elevator->displayInfo();
    }
    cout << endl;
}

Elevator* ElevatorSystem::findElevator(int elevatorId) const {
    if (elevatorId >= 0 && elevatorId < elevators.size()) {
        return elevators[elevatorId];
    }
    return nullptr;
} 

// ===== Request.cpp =====
Request::Request(int sourceFloor, int destinationFloor)
    : sourceFloor(sourceFloor), destinationFloor(destinationFloor) {
    isUp = destinationFloor > sourceFloor;
}

int Request::getSourceFloor() const { return sourceFloor; }
int Request::getDestinationFloor() const { return destinationFloor; }
bool Request::getIsUp() const { return isUp; } 

// ===== ElevatorDemo.cpp =====
int main() {
    ElevatorSystem system(2, 10); // 2 elevators, 10 floors
    
    // Add some requests
    system.addRequest(0, Request(0, 5));  // Elevator 0: Ground floor to 5th floor
    system.addRequest(1, Request(2, 7));  // Elevator 1: 2nd floor to 7th floor
    system.addRequest(0, Request(5, 3));  // Elevator 0: 5th floor to 3rd floor
    
    // Simulate elevator movement
    for (int i = 0; i < 15; i++) {
        system.displayStatus();
        system.step();
        
        // Wait for a second before next step
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    return 0;
} 

