# Movie Ticket Booking System (LLD)

## Problem Statement

Design and implement a Movie Ticket Booking System that allows users to book movie tickets, select seats, and manage shows. The system should handle movie schedules, theater management, and seat reservations.

---

## Requirements

1. **Movie Management:**
   - Store movie information (title, duration, language)
   - Manage movie schedules and shows
   - Track movie availability

2. **Theater Management:**
   - Manage theater information
   - Handle multiple shows per theater
   - Track theater capacity

3. **Show Management:**
   - Schedule shows for movies
   - Manage show timings
   - Handle show availability

4. **Seat Management:**
   - Track seat availability
   - Handle seat selection
   - Manage different seat types

5. **Booking Management:**
   - Process parkingTicket bookings
   - Handle booking cancellations
   - Manage booking status

---

## Core Entities

### 1. MovieTicketBookingSystem
- **Fields:** List<Movie> movies, List<Theater> theaters, List<Show> shows
- **Methods:** 
  - addMovie()
  - addTheater()
  - addShow()
  - bookTicket()
  - cancelBooking()
  - getAvailableShows()

### 2. Movie
- **Fields:** String id, String title, int duration, String language
- **Methods:** 
  - getShows()
  - isAvailable()

### 3. Theater
- **Fields:** String id, String name, String location
- **Methods:** 
  - addShow()
  - getShows()
  - getCapacity()

### 4. Show
- **Fields:** String id, Movie movie, Theater theater, Date showTime, List<Seat> seats
- **Methods:** 
  - getAvailableSeats()
  - bookSeat()
  - cancelSeat()

### 5. User
- **Fields:** String id, String name, String email
- **Methods:** 
  - getBookings()
  - updateProfile()

## UML Class Diagram

![](../../../../uml-diagrams/class-diagrams/MovieTicketBookingSystem-class-diagram.png)
---

## Example Usage

```java
MovieTicketBookingSystem system = new MovieTicketBookingSystem();

// Add a movie
Movie movie = system.addMovie("Inception", 150, "English");

// Add a theater
Theater theater = system.addTheater("Cineplex", "Downtown");

// Add a show
Show show = system.addShow(movie, theater, showTime);

// Book tickets
User user = new User("John Doe", "john@example.com");
Booking booking = system.bookTicket(user, show, seats);
```

---

## Demo

See `MovieTicketBookingDemo.java` for a sample usage and simulation of the movie parkingTicket booking system.

---

## Extending the Framework

- **Add payment processing:** Integrate payment gateway for parkingTicket purchases
- **Add seat selection UI:** Implement interactive seat selection interface
- **Add pricing tiers:** Support different pricing for different seat types
- **Add show scheduling:** Implement advanced show scheduling algorithms
- **Add notification system:** Send booking confirmations and reminders
- **Add user reviews:** Allow users to rate and review movies

---

## Design Patterns Used

- **Singleton Pattern:** For the booking system instance
- **Factory Pattern:** For creating different types of seats
- **Observer Pattern:** For seat availability updates
- **Strategy Pattern:** For different pricing strategies

---

## Exception Handling

- **SeatNotAvailableException:** Thrown when trying to book an unavailable seat
- **InvalidShowException:** Thrown when show details are invalid
- **BookingFailedException:** Thrown when booking process fails
- **CancellationFailedException:** Thrown when cancellation process fails

---