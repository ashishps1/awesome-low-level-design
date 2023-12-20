# Designing a Parking Lot System

This explores the low-level design of a parking lot system, a common problem in object-oriented design. 

We'll cover essential components and functionalities, breaking down requirements, use cases, and providing a Java implementation.

## Understanding the Requirements
A parking lot system manages vehicles parking in and out, with different parking spot sizes and rates. Key requirements include:
- **Vehicle Management:** Handling different types of vehicles.
- **Spot Management:** Managing various parking spot sizes.
- **Check-In/Out Process:** Recording the entry and exit of vehicles.
- **Payment Calculation:** Calculating parking fees.

## Core Use Cases
1. **Parking a Vehicle:** Assigning spots to vehicles and recording entry time.
2. **Unparking a Vehicle:** Removing a vehicle and calculating the fee.
3. **Spot Availability Check:** Checking for available spots for specific vehicles.

## UML and Class Diagrams
- **Class Diagram Concepts:**
  - `ParkingLot`: Manages the entire parking lot, including floors.
  - `ParkingFloor`: Represents individual floors with parking spots.
  - `ParkingSpot`: Abstract class for specific spot types (e.g., `CarSpot`).
  - `Vehicle`: Abstract class for various vehicle types (e.g., `Car`).

## Java Implementation
Here's a simplified version of Java code:

```java
class ParkingLot {
    private List<ParkingFloor> floors;
    // Other attributes and methods
}

class ParkingFloor {
    private List<ParkingSpot> spots;
    // Other attributes and methods
}

abstract class ParkingSpot {
    private boolean isAvailable;
    private Vehicle vehicle;
    // Other attributes and methods
}

class CarSpot extends ParkingSpot {
    // Car specific attributes
}

abstract class Vehicle {
    private String licenseNumber;
    // Other attributes and methods
}

class Car extends Vehicle {
    // Car specific attributes
}
```

