package airlinemanagementsystem;

import airlinemanagementsystem.booking.Booking;
import airlinemanagementsystem.flight.Flight;
import airlinemanagementsystem.payment.Payment;
import airlinemanagementsystem.seat.Seat;
import airlinemanagementsystem.seat.SeatType;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

public class AirlineManagementSystemDemo {
    public static void run() {
        AirlineManagementSystem airlineManagementSystem = new AirlineManagementSystem();

        // Create users
        Passenger passenger1 = new Passenger("U001", "John Doe", "john@example.com", "1234567890");

        // Create flights
        LocalDateTime departureTime1 = LocalDateTime.now().plusDays(1);
        LocalDateTime arrivalTime1 = departureTime1.plusHours(2);
        Flight flight1 = new Flight("F001", "New York", "London", departureTime1, arrivalTime1);

        LocalDateTime departureTime2 = LocalDateTime.now().plusDays(3);
        LocalDateTime arrivalTime2 = departureTime2.plusHours(5);
        Flight flight2 = new Flight("F002", "Paris", "Tokyo", departureTime2, arrivalTime2);

        airlineManagementSystem.addFlight(flight1);
        airlineManagementSystem.addFlight(flight2);

        // Create aircrafts
        Aircraft aircraft1 = new Aircraft("A001", "Boeing 747", 300);
        Aircraft aircraft2 = new Aircraft("A002", "Airbus A380", 500);
        airlineManagementSystem.addAircraft(aircraft1);
        airlineManagementSystem.addAircraft(aircraft2);

        // Search flights
        List<Flight> searchResults = airlineManagementSystem.searchFlights("New York", "London", LocalDate.now().plusDays(1));
        System.out.println("Search Results:");
        for (Flight flight : searchResults) {
            System.out.println("Flight: " + flight.getFlightNumber() + " - " + flight.getSource() + " to " + flight.getDestination());
        }

        Seat seat = new Seat("25A", SeatType.ECONOMY);

        // Book a flight
        Booking booking = airlineManagementSystem.bookFlight(flight1, passenger1, seat, 100);
        if (booking != null) {
            System.out.println("Booking successful. Booking ID: " + booking.getBookingNumber());
        } else {
            System.out.println("Booking failed.");
        }

        // Cancel a booking
        airlineManagementSystem.cancelBooking(booking.getBookingNumber());
        System.out.println("Booking cancelled.");
    }
}
