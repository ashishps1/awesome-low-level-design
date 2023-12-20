# Designing an Elevator System

This blog post explores the design and implementation of an Elevator System using object-oriented principles in Java, focusing on functionality, scalability, and user interaction.

## System Requirements

The Elevator System is designed to:

1. **Handle Multiple Requests:** Manage requests from different floors efficiently.
2. **Optimize Elevator Movement:** Allocate elevators based on requests to improve efficiency.
3. **Track Elevator Status:** Monitor the state and position of each elevator.
4. **Incorporate Safety Features:** Ensure key safety mechanisms are in place.

## Core Use Cases

1. **Requesting an Elevator:** Users can call elevators to their current floor.
2. **Transporting Passengers:** Elevators carry passengers to their desired floors.
3. **Managing Idle Elevators:** Efficiently allocate available elevators.

## UML/Class Diagrams

Key classes in the system include:

- `ElevatorSystem`: Manages multiple elevators.
- `Elevator`: Represents an individual elevator.
- `ElevatorControlPanel`: Interface for users to interact with an elevator.

## Java Implementation

### Elevator Class

This class represents an individual elevator.

```java
public class Elevator {
    private int currentFloor;
    private ElevatorState state;

    public Elevator() {
        this.currentFloor = 0; // Starting at ground floor
        this.state = ElevatorState.IDLE;
    }

    public void moveToFloor(int floor) {
        // Simulate elevator movement
        this.currentFloor = floor;
        this.state = ElevatorState.MOVING;
        // Assume elevator reaches the floor instantly
        this.state = ElevatorState.IDLE;
    }

    // Getters and setters...
}
```
### ElevatorSystem Class
```java
import java.util.*;

public class ElevatorSystem {
    private List<Elevator> elevators;

    public ElevatorSystem(int numberOfElevators) {
        elevators = new ArrayList<>();
        for (int i = 0; i < numberOfElevators; i++) {
            elevators.add(new Elevator());
        }
    }

    public void requestElevator(int floor) {
        Elevator closestElevator = findClosestElevator(floor);
        if (closestElevator != null) {
            closestElevator.moveToFloor(floor);
        }
    }

    private Elevator findClosestElevator(int floor) {
        Elevator closest = null;
        int minDistance = Integer.MAX_VALUE;
        for (Elevator elevator : elevators) {
            int distance = Math.abs(elevator.getCurrentFloor() - floor);
            if (distance < minDistance && elevator.getState() == ElevatorState.IDLE) {
                closest = elevator;
                minDistance = distance;
            }
        }
        return closest;
    }

    // Other necessary methods...
}
```
### ElevatorControlPanel Class
```java
public class ElevatorControlPanel {
    private Elevator elevator;

    public ElevatorControlPanel(Elevator elevator) {
        this.elevator = elevator;
    }

    public void goToFloor(int floor) {
        elevator.moveToFloor(floor);
    }

    // Other necessary methods...
}
```