# Elevator System (LLD)

## Problem Statement

Design and implement an Elevator System that can handle multiple requests, move between floors, and manage direction and state efficiently.

---

## Requirements

- **Multiple Elevator:** The system manages multiple elevators.
- **Request Handling:** The system can handle requests to move to specific floors in a given direction (UP/DOWN).
- **Direction Management:** The elevator maintains and updates its current direction (UP, DOWN, IDLE).
- **State Management:** The elevator tracks its current floor, direction, and pending requests.
- **Efficient Movement:** The elevator processes requests in an efficient order (e.g., all UP requests, then all DOWN requests).
- **Extensibility:** Easy to add more elevators or advanced scheduling algorithms.

---

## Core Entities

- **Elevator:** Represents the elevator, manages its state, direction, and request queue.
- **ElevatorController:** Handles incoming requests and delegates them to the elevator.
- **Request:** Represents a request to move to a specific floor in a given direction.
- **Direction (enum):** UP, DOWN, IDLE.

---

## Class Design

### 1. Elevator
- **Fields:** currentFloor, direction, List<Request> requests, isMoving, etc.
- **Methods:** addRequest(Request), move(), openDoor(), closeDoor(), processNextRequest(), getCurrentFloor(), getDirection(), etc.

### 2. ElevatorController
- **Fields:** Elevator elevator
- **Methods:** requestElevator(int floor, Direction direction), step(), etc.

### 3. Request
- **Fields:** int floor, Direction direction

### 4. Direction (enum)
- Values: UP, DOWN, IDLE

---

## Example Usage

```java
ElevatorController controller = new ElevatorController();
controller.requestElevator(5, Direction.UP);
controller.requestElevator(2, Direction.DOWN);

// Simulate elevator steps
for (int i = 0; i < 10; i++) {
    controller.step();
}
```

---

## Demo

See `ElevatorSystemDemo.java` for a sample usage and simulation of the elevator system.

---

## Extending the Framework

- **Add multiple elevators:** Create a list of `Elevator` objects and update the controller logic.
- **Advanced scheduling:** Implement algorithms for optimal elevator assignment.
- **Add features:** Such as maintenance mode, emergency stop, or floor display.

---