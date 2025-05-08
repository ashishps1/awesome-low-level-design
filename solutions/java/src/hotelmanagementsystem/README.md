# Hotel Management System (LLD)

## Problem Statement

Design and implement a Hotel Management System that manages hotel rooms, reservations, and guest information. The system should handle room bookings, check-ins, check-outs, and maintain room status.

---

## Requirements

1. **Room Management:**
   - Track different types of rooms (STANDARD, DELUXE, SUITE)
   - Manage room availability and status
   - Handle room pricing and features

2. **Reservation Management:**
   - Create and manage reservations
   - Handle check-in and check-out processes
   - Track reservation status (CONFIRMED, CANCELLED, CHECKED_IN, CHECKED_OUT)

3. **Guest Management:**
   - Store guest information
   - Track guest history
   - Handle guest preferences

4. **Room Status Tracking:**
   - Monitor room availability (AVAILABLE, OCCUPIED, MAINTENANCE)
   - Update room status based on reservations
   - Handle room maintenance requests

5. **Payment Integration:**
   - Process room payments
   - Handle different payment methods
   - Generate invoices

---

## Core Entities

### 1. HotelManagementSystem
- **Fields:** List<Room> rooms, List<Reservation> reservations, List<Guest> guests
- **Methods:** 
  - addRoom()
  - makeReservation()
  - checkIn()
  - checkOut()
  - getAvailableRooms()
  - cancelReservation()

### 2. Room
- **Fields:** String roomNumber, RoomType type, double price, RoomStatus status
- **Methods:** 
  - isAvailable()
  - updateStatus()
  - getPrice()

### 3. Guest
- **Fields:** String id, String name, String email, String phoneNumber
- **Methods:** 
  - updateProfile()
  - getReservations()

### 4. Reservation
- **Fields:** String id, Guest guest, Room room, Date checkInDate, Date checkOutDate, ReservationStatus status
- **Methods:** 
  - confirm()
  - cancel()
  - checkIn()
  - checkOut()

### 5. RoomType (Enum)
- **Values:** STANDARD, DELUXE, SUITE

### 6. RoomStatus (Enum)
- **Values:** AVAILABLE, OCCUPIED, MAINTENANCE

### 7. ReservationStatus (Enum)
- **Values:** CONFIRMED, CANCELLED, CHECKED_IN, CHECKED_OUT

---

## Example Usage

```java
HotelManagementSystem system = new HotelManagementSystem();

// Add a room
Room room = system.addRoom("101", RoomType.DELUXE, 150.0);

// Create a guest
Guest guest = new Guest("John Doe", "john@example.com", "1234567890");

// Make a reservation
Reservation reservation = system.makeReservation(guest, room, checkInDate, checkOutDate);

// Check in
system.checkIn(reservation);

// Check out
system.checkOut(reservation);
```

---

## Demo

See `HotelManagementSystemDemo.java` for a sample usage and simulation of the hotel management system.

---

## Extending the Framework

- **Add room service:** Track room service requests and delivery
- **Add housekeeping:** Manage housekeeping schedules and tasks
- **Add loyalty program:** Implement guest loyalty points and rewards
- **Add inventory management:** Track hotel supplies and amenities
- **Add reporting system:** Generate occupancy and revenue reports
- **Add notification system:** Send booking confirmations and reminders

---

## Design Patterns Used

- **Singleton Pattern:** For the hotel management system instance
- **Factory Pattern:** For creating different types of rooms
- **Observer Pattern:** For room status updates and notifications
- **Strategy Pattern:** For different pricing strategies

---

## Exception Handling

- **RoomNotAvailableException:** Thrown when trying to book an unavailable room
- **InvalidReservationException:** Thrown when reservation details are invalid
- **CheckInException:** Thrown when check-in process fails
- **CheckOutException:** Thrown when check-out process fails

---