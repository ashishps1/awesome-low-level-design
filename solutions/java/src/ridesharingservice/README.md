# Ride Sharing Service (LLD)

## Problem Statement

Design and implement a Ride Sharing Service that allows riders to request rides, drivers to accept trips, and the system to manage trip assignments, payments, and trip status.

---

## Requirements

- **User Management:** The system manages both riders and drivers.
- **Location Management:** The system tracks the current location of drivers and riders.
- **Trip Request:** Riders can request rides by specifying pickup and drop-off locations.
- **Driver Assignment:** The system assigns available drivers to ride requests based on proximity and availability.
- **Trip Management:** The system tracks the status of each trip (e.g., REQUESTED, ONGOING, COMPLETED, CANCELLED).
- **Payment Processing:** The system processes payments for completed trips.
- **Driver Status:** The system tracks driver availability (e.g., AVAILABLE, ON_TRIP, OFFLINE).
- **Extensibility:** Easy to add new features such as ratings, ride pooling, or surge pricing.

---

## Core Entities

- **RideSharingService:** Main class that manages riders, drivers, trips, and payments.
- **Rider:** Represents a rider who can request trips.
- **Driver:** Represents a driver with current status and location.
- **Trip:** Represents a ride, including rider, driver, locations, status, and payment.
- **Location:** Represents a geographic location (latitude, longitude).
- **TripStatus (enum):** REQUESTED, ONGOING, COMPLETED, CANCELLED.
- **DriverStatus (enum):** AVAILABLE, ON_TRIP, OFFLINE.
- **Payment (in payment/):** Represents a payment transaction for a trip.
- **User:** Base class for Rider and Driver (if applicable).

---

## Class Design

### 1. RideSharingService
- **Fields:** List<Rider> riders, List<Driver> drivers, List<Trip> trips, PaymentProcessor paymentProcessor
- **Methods:** registerRider(Rider), registerDriver(Driver), requestTrip(Rider, Location, Location), assignDriver(Trip), startTrip(Trip), completeTrip(Trip), processPayment(Trip, Payment), updateDriverStatus(Driver, DriverStatus), etc.

### 2. Rider
- **Fields:** int id, String name, Location currentLocation

### 3. Driver
- **Fields:** int id, String name, Location currentLocation, DriverStatus status

### 4. Trip
- **Fields:** int id, Rider rider, Driver driver, Location pickup, Location dropoff, TripStatus status, Payment payment

### 5. Location
- **Fields:** double latitude, double longitude

### 6. TripStatus (enum)
- Values: REQUESTED, ONGOING, COMPLETED, CANCELLED

### 7. DriverStatus (enum)
- Values: AVAILABLE, ON_TRIP, OFFLINE

### 8. Payment (in payment/)
- **Fields:** int id, double amount, String method, PaymentStatus status

### 9. PaymentProcessor (in payment/)
- **Methods:** process(Payment), validate(Payment)

### 10. User
- **Fields:** int id, String name

---

## Example Usage

```java
RideSharingService service = new RideSharingService();
Rider alice = new Rider(1, "Alice", new Location(12.9716, 77.5946));
Driver bob = new Driver(2, "Bob", new Location(12.9718, 77.5940), DriverStatus.AVAILABLE);

service.registerRider(alice);
service.registerDriver(bob);

Trip trip = service.requestTrip(alice, alice.getCurrentLocation(), new Location(12.9352, 77.6245));
service.assignDriver(trip);
service.startTrip(trip);
// ... after trip completion
Payment payment = new Payment(1, 250.0, "CREDIT_CARD");
service.completeTrip(trip);
service.processPayment(trip, payment);
```

---

## Demo

See `RideSharingServiceDemo.java` for a sample usage and simulation of the ride sharing service.

---

## Extending the Framework

- **Add ratings and reviews:** Allow riders and drivers to rate each other.
- **Add ride pooling:** Support multiple riders sharing a trip.
- **Add surge pricing:** Adjust pricing based on demand and supply.

---