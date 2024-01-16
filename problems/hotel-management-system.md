# Designing a Hotel Management System

In this article, we will explore the design and implementation of a Hotel Management System (HMS) using object-oriented principles in Java. 

The HMS is designed to streamline hotel operations including room booking, customer management, and service provision.

## System Requirements

The HMS will facilitate:

1. **Room Booking Management:** Manage bookings for various types of rooms.
2. **Customer Management:** Handle customer information and booking history.
3. **Room Service Management:** Manage orders for food and other services.
4. **Billing:** Generate bills for customers based on their usage of services.

## Core Use Cases

1. **Booking a Room:** Customers can book different types of rooms.
2. **Managing Customer Profiles:** Storing and retrieving customer details.
3. **Ordering Room Services:** Placing orders for room-related services.
4. **Generating Bills:** Calculating and producing bills for customers.

## Key Classes:
- `Hotel`: Manages the overall hotel operations.
- `Room`: Represents individual rooms in the hotel.
- `Customer`: Manages information about customers.
- `Booking`: Represents a room booking by a customer.
- `Service`: Represents additional services provided to customers.

## Java Implementation

### Room Class

This class represents a hotel room.

```java
public class Room {
    private String roomNumber;
    private String roomType;
    private boolean isBooked;

    public Room(String roomNumber, String roomType) {
        this.roomNumber = roomNumber;
        this.roomType = roomType;
        this.isBooked = false;
    }

    public void bookRoom() {
        isBooked = true;
    }

    public void vacateRoom() {
        isBooked = false;
    }

    // Getters and setters...
}
```

### Customer Class
```java
public class Customer {
    private String customerId;
    private String name;
    private String phone;

    public Customer(String customerId, String name, String phone) {
        this.customerId = customerId;
        this.name = name;
        this.phone = phone;
    }
    // Getters and setters...
}
```
### Booking Class
```java
import java.time.LocalDate;

public class Booking {
    private Room room;
    private Customer customer;
    private LocalDate checkInDate;
    private LocalDate checkOutDate;

    public Booking(Room room, Customer customer, LocalDate checkIn, LocalDate checkOut) {
        this.room = room;
        this.customer = customer;
        this.checkInDate = checkIn;
        this.checkOutDate = checkOut;
        room.bookRoom();
    }

    // Method to complete booking
    public void completeBooking() {
        room.vacateRoom();
    }

    // Getters and setters...
}
```
### Hotel Class
```java
import java.util.ArrayList;
import java.util.List;

public class Hotel {
    private String hotelName;
    private List<Room> rooms;
    private List<Booking> bookings;

    public Hotel(String hotelName) {
        this.hotelName = hotelName;
        this.rooms = new ArrayList<>();
        this.bookings = new ArrayList<>();
    }

    public void addRoom(Room room) {
        rooms.add(room);
    }

    public Booking bookRoom(String roomNumber, Customer customer, LocalDate checkIn, LocalDate checkOut) {
        Room room = rooms.stream()
                         .filter(r -> r.getRoomNumber().equals(roomNumber) && !r.isBooked())
                         .findFirst().orElse(null);
        if (room != null) {
            Booking booking = new Booking(room, customer, checkIn, checkOut);
            bookings.add(booking);
            return booking;
        }
        return null;
    }

    // Getters and setters...
}
```