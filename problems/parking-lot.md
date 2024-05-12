# Designing a Parking Lot System

This article explores the low-level design of a parking lot system, a common problem in object-oriented design. 

We'll cover essential components and functionalities, breaking down requirements, use cases, and providing a Java implementation.

## Understanding the Requirements
A parking lot system manages vehicles parking in and out, with different parking spot sizes and rates. Key requirements include:
- **Parking Space Management:** Track the availability of parking spaces.
- **Vehicle Management:** Handle the entry and exit of vehicles.
- **Fee Calculation:** Calculate parking fees based on parking duration.
- **Parking Lot Capacity:** Support different types of vehicles with designated spots (e.g., compact, large, handicapped).

## Core Use Cases
1. **Parking a Vehicle:** Assigning spots to vehicles and recording entry time.
2. **Unparking a Vehicle:** Removing a vehicle and calculating the fee.
3. **Spot Availability Check:** Checking for available spots for specific vehicles.
4. **Handling Different Vehicle Types**

## Key Classes:
- `ParkingLot`: Manages the entire parking lot, including floors.
- `ParkingFloor`: Represents individual floors with parking spots.
- `ParkingSpot`: Represents an individual parking spot.
- `Vehicle`: Abstract class for various vehicle types (e.g., `Car`).
- `ParkingTicket`: Represents a parking ticket issued to a vehicle.
- `FeeCalculator`: Calculates parking fees.

## Java Implementation
Here's a simplified version of Java code:

### Vehicle Class
```java
abstract class Vehicle {
    private String registrationNumber;
    protected VehicleType type;
    
    public Vehicle(String registrationNumber, VehicleType type) {
        this.registrationNumber = registrationNumber;
        this.type = type;
    }

    // Other attributes and methods
}

class Car extends Vehicle {
    // Car specific attributes
}

enum VehicleType {
    COMPACT, LARGE, HANDICAPPED
}
```
### ParkingSpot Class
```java
public class ParkingSpot {
    private String id;
    private VehicleType type;
    private boolean isOccupied;

    public ParkingSpot(String id, VehicleType type) {
        this.id = id;
        this.type = type;
        this.isOccupied = false;
    }

    public void occupySpot() {
        isOccupied = true;
    }

    public void freeSpot() {
        isOccupied = false;
    }

    // Getters and setters...
}
```
### ParkingTicket Class
```java
import java.util.Date;

public class ParkingTicket {
    private String ticketId;
    private Date issuedAt;
    private Date paidAt;
    private double fee;

    public ParkingTicket(String ticketId) {
        this.ticketId = ticketId;
        this.issuedAt = new Date();
    }

    public void markPaid(double fee) {
        this.paidAt = new Date();
        this.fee = fee;
    }

    // Getters and setters...
}
```
### FeeCalculator Class
```java
public class FeeCalculator {
    public double calculateFee(Date issuedAt, Date paidAt) {
        // Assume a method to calculate fee based on issuedAt and paidAt
        return 0.0; // Placeholder
    }
}
```
### ParkingLot Class
```java
class ParkingLot {
    private List<ParkingFloor> parkingFloors;
    private List<ParkingTicket> issuedTickets;

    public ParkingLot() {
        this.parkingFloors = new ArrayList<>();
        this.issuedTickets = new ArrayList<>();
    }

    public ParkingSpot findAvailableSpot(VehicleType type) {
        // Logic to find an available spot based on vehicle type
        return null; // Placeholder
    }

    public ParkingTicket issueTicket(Vehicle vehicle) {
        ParkingSpot spot = findAvailableSpot(vehicle.getType());
        if (spot != null) {
            spot.occupySpot();
            ParkingTicket ticket = new ParkingTicket(generateTicketId());
            issuedTickets.add(ticket);
            return ticket;
        }
        return null;
    }

    public void processPayment(ParkingTicket ticket, double fee) {
        ticket.markPaid(fee);
        // Additional logic for processing payment
    }

    private String generateTicketId() {
        return "TICKET_" + System.currentTimeMillis();
    }

    // Other necessary methods...
}
```
### ParkingFloor
```java
class ParkingFloor {
    private List<ParkingSpot> spots;
    // Other attributes and methods
}

public class ParkingSpot {
    private String id;
    private VehicleType type;
    private boolean isOccupied;
    
    public ParkingSpot(String id, VehicleType type) {
        this.id = id;
        this.type = type;
        this.isOccupied = false;
    }

    public void occupySpot() {
        isOccupied = true;
    }

    public void freeSpot() {
        isOccupied = false;
    }
}

class CarSpot extends ParkingSpot {
    // Car specific attributes
}
```

