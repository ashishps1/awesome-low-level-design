# Designing a Concert Ticket Booking System

In this article, we delve into the object-oriented design and implementation of a Concert Ticket Booking System using Java. 

This system facilitates booking tickets for concerts and managing events.

## System Requirements

The Concert Ticket Booking System should:

1. **Event Management**: Manage concert details including dates, venues, and artists.
2. **User Account Management**: Handle user registrations and profiles.
3. **Ticket Booking Process**: Enable users to book tickets and select seats.
4. **Payment Processing**: Handle ticket payments and issue receipts.
5. **Ticket Cancellation and Refund**: Manage cancellations and refunds.

## Core Use Cases

1. **Creating and Managing Concert Events**
2. **Registering and Managing User Accounts**
3. **Booking and Canceling Tickets**
4. **Processing Payments and Issuing Tickets**
5. **Handling Refunds**

## UML/Class Diagrams

Key Classes:

- `ConcertTicketBookingSystem`: Manages the system.
- `User`: Represents a customer.
- `Concert`: Represents a concert event.
- `Ticket`: Manages ticket details.
- `Payment`: Handles payment transactions.

## Java Implementation

### Concert Class

Represents a concert event.

```java
import java.util.Date;

public class Concert {
    private String concertId;
    private String title;
    private Date date;
    private String venue;
    private int totalSeats;
    private int availableSeats;

    public Concert(String concertId, String title, Date date, String venue, int totalSeats) {
        this.concertId = concertId;
        this.title = title;
        this.date = date;
        this.venue = venue;
        this.totalSeats = totalSeats;
        this.availableSeats = totalSeats;
    }

    public boolean bookSeats(int numberOfSeats) {
        if (numberOfSeats <= availableSeats) {
            availableSeats -= numberOfSeats;
            return true;
        }
        return false;
    }

    // Getters and setters...
}
```
### User Class
Manages user account information.
```java
public class User {
    private String userId;
    private String name;
    private String email;

    public User(String userId, String name, String email) {
        this.userId = userId;
        this.name = name;
        this.email = email;
    }

    // Getters and setters...
}
```
### Ticket Class
Represents a concert ticket.
```java
public class Ticket {
    private String ticketId;
    private Concert concert;
    private User user;
    private int numberOfSeats;
    private double totalPrice;

    public Ticket(String ticketId, Concert concert, User user, int numberOfSeats, double pricePerSeat) {
        this.ticketId = ticketId;
        this.concert = concert;
        this.user = user;
        this.numberOfSeats = numberOfSeats;
        this.totalPrice = pricePerSeat * numberOfSeats;
    }

    // Getters and setters...
}
```
### Payment Class
Handles payment transactions.
```java
public class Payment {
    private String paymentId;
    private double amount;
    private PaymentStatus status;

    public Payment(String paymentId, double amount) {
        this.paymentId = paymentId;
        this.amount = amount;
        this.status = PaymentStatus.PENDING;
    }

    public void completePayment() {
        this.status = PaymentStatus.COMPLETED;
    }

    // Getters and setters...
}

enum PaymentStatus {
    PENDING, COMPLETED, FAILED
}
```
### ConcertTicketBookingSystem Class
Manages the concert ticket booking system operations.

```java
import java.util.ArrayList;
import java.util.List;

public class ConcertTicketBookingSystem {
    private List<User> users;
    private List<Concert> concerts;
    private List<Ticket> tickets;

    public ConcertTicketBookingSystem() {
        this.users = new ArrayList<>();
        this.concerts = new ArrayList<>();
        this.tickets = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public void addConcert(Concert concert) {
        concerts.add(concert);
    }

    public Ticket bookTicket(String userId, String concertId, int numberOfSeats) {
        User user = findUserById(userId);
        Concert concert = findConcertById(concertId);

        if (user != null && concert != null && concert.bookSeats(numberOfSeats)) {
            double pricePerSeat = // Assume a method to get price per seat
            Ticket ticket = new Ticket(generateTicketId(), concert, user, numberOfSeats, pricePerSeat);
            tickets.add(ticket);
            return ticket;
        }
        return null;
    }

    private User findUserById(String userId) {
        for (User user : users) {
            if (user.getUserId().equals(userId)) {
                return user;
            }
        }
        return null;
    }

    private Concert findConcertById(String concertId) {
        for (Concert concert : concerts) {
            if (concert.getConcertId().equals(concertId)) {
                return concert;
            }
        }
        return null;
    }

    private String generateTicketId() {
        return "TICKET_" + System.currentTimeMillis();
    }

    // Other necessary methods...
}
```