# Concert Ticket Booking System (LLD)

## Problem Statement

Design and implement a Concert Ticket Booking System that allows users to book seats for concerts. The system should manage concert details, seat availability, and handle bookings with proper validation.

---

## Requirements

- **Concert Management:** The system manages concert details including name, date, venue, and available seats.
- **Seat Management:** The system tracks different types of seats (VIP, STANDARD, ECONOMY) and their availability.
- **Booking Management:** Users can book seats, and the system handles booking status (CONFIRMED, CANCELLED).
- **User Management:** The system maintains user information for bookings.
- **Validation:** The system prevents double bookings and handles seat availability checks.

---

## Core Entities

- **ConcertTicketBookingSystem:** Main class that manages concerts, bookings, and seat allocation.
- **Concert:** Represents a concert with its details and seat management.
- **Seat:** Represents a seat with its type, status, and booking information.
- **User:** Represents a user who can book tickets.
- **Booking:** Represents a booking with its status and associated details.
- **SeatType:** Enum for different seat categories (VIP, STANDARD, ECONOMY).
- **SeatStatus:** Enum for seat states (AVAILABLE, BOOKED).
- **BookingStatus:** Enum for booking states (CONFIRMED, CANCELLED).

---

## Class Design

### 1. ConcertTicketBookingSystem
- **Fields:** List<Concert> concerts, List<Booking> bookings
- **Methods:** addConcert(), bookSeat(), cancelBooking(), getAvailableSeats(), etc.

### 2. Concert
- **Fields:** String name, String date, String venue, List<Seat> seats
- **Methods:** addSeat(), getAvailableSeats(), bookSeat(), etc.

### 3. Seat
- **Fields:** String seatNumber, SeatType type, SeatStatus status, Booking booking
- **Methods:** isAvailable(), book(), cancel(), etc.

### 4. User
- **Fields:** String name, String email

### 5. Booking
- **Fields:** String bookingId, User user, Concert concert, Seat seat, BookingStatus status
- **Methods:** confirm(), cancel(), etc.

### 6. Enums
- **SeatType:** VIP, STANDARD, ECONOMY
- **SeatStatus:** AVAILABLE, BOOKED
- **BookingStatus:** CONFIRMED, CANCELLED

---

## Example Usage

```java
ConcertTicketBookingSystem system = new ConcertTicketBookingSystem();

// Add a concert
Concert concert = system.addConcert("Rock Concert", "2024-12-31", "Stadium");

// Book a seat
User user = new User("John Doe", "john@example.com");
Booking booking = system.bookSeat(concert, "A1", user);

// Cancel booking
system.cancelBooking(booking);
```

---

## Demo

See `ConcertTicketBookingSystemDemo.java` for a sample usage and simulation of the booking system.

---

## Extending the Framework

- **Add payment processing:** Integrate payment gateway for ticket purchases
- **Add waitlist functionality:** Handle seat waitlist when fully booked
- **Add discount management:** Support for different pricing tiers and discounts
- **Add notification system:** Send booking confirmations and updates

---

## Design Patterns Used

- **Singleton Pattern:** For managing the booking system instance
- **Factory Pattern:** For creating different types of seats
- **Observer Pattern:** For notifying users about booking status changes

---