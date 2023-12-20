# Designing an Airline Management System

This blog delves into the object-oriented design and implementation of an Airline Management System using Java. 

This system will handle various aspects of airline operations including managing flights, passengers, crew, and aircraft.

## System Requirements

The Airline Management System should:

1. **Flight Management:** Create and schedule flights.
2. **Passenger Management:** Manage passenger bookings and check-ins.
3. **Crew Management:** Assign crew members to flights.
4. **Aircraft Management:** Track aircraft and maintenance schedules.

## Core Use Cases

1. **Scheduling and Managing Flights**
2. **Booking and Managing Passenger Seats**
3. **Assigning Crew to Flights**
4. **Managing Aircraft**

## UML/Class Diagrams

Key Classes:

- `AirlineManagementSystem`: Manages the entire system.
- `Flight`: Represents a flight.
- `Passenger`: Represents a passenger.
- `CrewMember`: Represents a flight crew member.
- `Aircraft`: Represents an aircraft.

## Java Implementation

### Flight Class

Represents a flight.

```java
import java.util.Date;

public class Flight {
    private String flightNumber;
    private Aircraft aircraft;
    private Date departureTime;
    private String origin;
    private String destination;

    public Flight(String flightNumber, Aircraft aircraft, Date departureTime, String origin, String destination) {
        this.flightNumber = flightNumber;
        this.aircraft = aircraft;
        this.departureTime = departureTime;
        this.origin = origin;
        this.destination = destination;
    }

    // Getters and setters...
}
```
### Passenger Class
Manages passenger information.
```java
public class Passenger {
    private String name;
    private String passportNumber;

    public Passenger(String name, String passportNumber) {
        this.name = name;
        this.passportNumber = passportNumber;
    }

    // Getters and setters...
}
```
### CrewMember Class
Represents a crew member.
```java
public class CrewMember {
    private String name;
    private String employeeId;

    public CrewMember(String name, String employeeId) {
        this.name = name;
        this.employeeId = employeeId;
    }

    // Getters and setters...
}
```
### Aircraft Class
Represents an aircraft.
```java
public class Aircraft {
    private String registrationNumber;
    private String model;
    private int totalSeats;

    public Aircraft(String registrationNumber, String model, int totalSeats) {
        this.registrationNumber = registrationNumber;
        this.model = model;
        this.totalSeats = totalSeats;
    }

    // Getters and setters...
}
```
### AirlineManagementSystem Class
Manages overall airline operations.
```java
import java.util.ArrayList;
import java.util.List;

public class AirlineManagementSystem {
    private List<Flight> flights;
    private List<Passenger> passengers;
    private List<CrewMember> crewMembers;
    private List<Aircraft> aircrafts;

    public AirlineManagementSystem() {
        this.flights = new ArrayList<>();
        this.passengers = new ArrayList<>();
        this.crewMembers = new ArrayList<>();
        this.aircrafts = new ArrayList<>();
    }

    public void addFlight(Flight flight) {
        flights.add(flight);
    }

    public void addPassenger(Passenger passenger) {
        passengers.add(passenger);
    }

    public void addCrewMember(CrewMember crewMember) {
        crewMembers.add(crewMember);
    }

    public void addAircraft(Aircraft aircraft) {
        aircrafts.add(aircraft);
    }

    // Other necessary methods...
}
```