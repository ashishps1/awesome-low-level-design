# Parking Lot System (LLD)

## Problem Statement

Design and implement a Parking Lot Management System that supports parking and unparking of vehicles, ticket generation, fee calculation, and management of multiple floors and spot types.

---

## Requirements

- **Multiple Floors:** The parking lot can have multiple floors.
- **Parking Spots:** Each floor has multiple parking spots of different types (e.g., car, bike, truck).
- **Vehicle Types:** Support for different vehicle types (see `vehicletype/`).
- **Ticketing:** Generate a ticket when a vehicle is parked.
- **Unparking:** Allow vehicles to unpark and calculate the parking fee.
- **Fee Calculation:** Support for different fee strategies (see `fee/`).
- **Spot Allocation:** Allocate the nearest available spot of the correct type.
- **Extensibility:** Easy to add new vehicle types, spot types, or fee strategies.

---

## Core Entities

- **ParkingLot:** Main class managing the entire parking lot, floors, and overall operations.
- **ParkingFloor:** Represents a single floor in the parking lot, manages its spots.
- **ParkingSpot:** Represents an individual parking spot, knows its type and occupancy.
- **Ticket:** Represents a parking ticket issued when a vehicle is parked.
- **VehicleType (in `vehicletype/`):** Enum or classes for different vehicle types.
- **Fee Calculation (in `fee/`):** Classes for calculating parking fees based on duration and vehicle type.

---

## Class Design

### 1. ParkingLot
- **Methods:**
  - `parkVehicle(Vehicle vehicle)`
  - `unparkVehicle(String ticketId)`
  - `addFloor(ParkingFloor floor)`
  - `getAvailableSpots()`
- **Fields:** List of floors, mapping of tickets, etc.

### 2. ParkingFloor
- **Methods:**
  - `getAvailableSpot(VehicleType type)`
  - `parkVehicle(Vehicle vehicle)`
  - `unparkVehicle(String spotId)`
- **Fields:** List of spots, floor number.

### 3. ParkingSpot
- **Methods:**
  - `isAvailable()`
  - `assignVehicle(Vehicle vehicle)`
  - `removeVehicle()`
- **Fields:** Spot ID, type, current vehicle.

### 4. Ticket
- **Fields:** Ticket ID, vehicle info, entry time, spot info.

### 5. VehicleType (in `vehicletype/`)
- Enum or classes for vehicle types (Car, Bike, Truck, etc.)

### 6. Fee Calculation (in `fee/`)
- **Methods:** `calculateFee(Ticket ticket, Date exitTime)`
- **Extensible:** Add new strategies for fee calculation.

---

## Design Patterns Used

- **Strategy Pattern:** For fee calculation strategies.
- **Factory Pattern:** (If used) For creating vehicles or spots.
- **Singleton Pattern:** (If used) For ParkingLot instance.

---

## Example Usage

```java
ParkingLot lot = new ParkingLot();
lot.addFloor(new ParkingFloor(...));
Ticket ticket = lot.parkVehicle(new Car("KA-01-1234"));
lot.unparkVehicle(ticket.getId());
```

---

## Demo

See `ParkingLotDemo.java` for a sample usage of the parking lot system.

---

## Extending the Framework

- **Add a new vehicle type:** Update or add to `vehicletype/`.
- **Add a new fee strategy:** Implement a new class in `fee/`.
- **Add new spot types or floors:** Extend `ParkingSpot` or `ParkingFloor`.

---