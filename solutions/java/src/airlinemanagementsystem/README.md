# Airline Management System (LLD)

## Problem Statement

Design and implement an Airline Management System that allows users to book flights, manage passengers, handle seat assignments, process payments, and track bookings and flights.

---

## Requirements

- **Flight Management:** The system manages flights, each with a unique flight number, aircraft, source, destination, and schedule.
- **Aircraft Management:** Each flight is associated with an aircraft, which has a model and a set of seats.
- **Seat Management:** The system manages seat assignments and availability for each flight.
- **Passenger Management:** Passengers can be added, updated, and associated with bookings.
- **Booking Management:** Users can book flights, and the system tracks bookings, assigned seats, and passengers.
- **Payment Processing:** The system processes payments for bookings.
- **Extensibility:** Easy to add new features such as loyalty programs, meal selection, or multi-leg journeys.

---

## Core Entities

- **AirlineManagementSystem:** Main class that manages flights, bookings, passengers, and payments.
- **Flight:** Represents a flight with flight number, aircraft, source, destination, schedule, and seats.
- **Aircraft:** Represents an aircraft with a model and a set of seats.
- **Seat:** Represents a seat on an aircraft, with seat number, class, and availability.
- **Passenger:** Represents a user with ID, name, and contact details.
- **Booking:** Represents a booking, including user(s), flight, seat(s), and payment.
- **Payment (in payment/):** Represents a payment transaction for a booking.

---

## Class Design

## UML Class Diagram

![](../../../../uml-diagrams/class-diagrams/airlinemanagementsystem-class-diagram.png)

### 1. AirlineManagementSystem

- **Fields:** List<Flight> flights, List<Booking> bookings, List<Passenger> passengers, PaymentProcessor paymentProcessor
- **Methods:** addFlight(Flight), addPassenger(Passenger), bookFlight(Passenger, Flight, Seat, Payment), getAvailableSeats(Flight), getBookings(Passenger), etc.

### 2. Flight (in flight/)

- **Fields:** String flightNumber, Aircraft aircraft, String source, String destination, Date schedule, List<Seat> seats

### 3. Aircraft

- **Fields:** String model, List<Seat> seats

### 4. Seat (in seat/)

- **Fields:** String seatNumber, String seatClass, boolean isAvailable

### 5. Passenger

- **Fields:** int id, String name, String contactInfo

### 6. Booking (in booking/)

- **Fields:** int id, Passenger user, Flight flight, List<Seat> seats, Payment payment

### 7. Payment (in payment/)

- **Fields:** int id, double amount, String method, PaymentStatus status

### 8. PaymentProcessor (in payment/)

- **Methods:** process(Payment), validate(Payment)

---

## Example Usage

```java
AirlineManagementSystem system = new AirlineManagementSystem();
Aircraft aircraft = new Aircraft("Boeing 737", seatList);
Flight flight = new Flight("AI101", aircraft, "DEL", "BOM", new Date(), seatList);
system.addFlight(flight);

Passenger alice = new Passenger(1, "Alice", "alice@email.com");
system.addPassenger(alice);

Seat seat = flight.getAvailableSeats().get(0);
Payment payment = new Payment(1, 5000.0, "CREDIT_CARD");
system.bookFlight(alice, flight, seat, payment);
```

---

## Demo

See `AirlineManagementSystemDemo.java` for a sample usage and simulation of the airline management system.

---

## Extending the Framework

- **Add loyalty programs:** Track frequent flyer points and rewards.
- **Add meal selection:** Allow passengers to select meals during booking.
- **Add multi-leg journeys:** Support bookings with multiple connecting flights.

---
