package airlinemanagementsystem;

import airlinemanagementsystem.booking.Booking;
import airlinemanagementsystem.flight.Flight;
import airlinemanagementsystem.seat.Seat;
import airlinemanagementsystem.seat.SeatType;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

public class AirlineManagementSystemDemo {
    public static void run() {
        AirlineManagementSystem airlineManagementSystem = new AirlineManagementSystem();

        // Create passengers
        Passenger passenger1 = airlineManagementSystem.addPassenger("John Doe", "john@example.com");
        Passenger passenger2 = airlineManagementSystem.addPassenger("John Smith", "smith@example.com");

        // Create aircrafts
        Aircraft aircraft1 = airlineManagementSystem.addAircraft("A001", "Boeing 747", 300);
        Aircraft aircraft2 = airlineManagementSystem.addAircraft("A002", "Airbus A380", 500);

        // Create flights
        LocalDateTime departureTime1 = LocalDateTime.now().plusDays(1);
        LocalDateTime arrivalTime1 = departureTime1.plusHours(2);
        Flight flight1 = airlineManagementSystem.addFlight("New York", "London", departureTime1, arrivalTime1, aircraft1.getTailNumber());

        LocalDateTime departureTime2 = LocalDateTime.now().plusDays(3);
        LocalDateTime arrivalTime2 = departureTime2.plusHours(5);
        Flight flight2 = airlineManagementSystem.addFlight("Paris", "Tokyo", departureTime2, arrivalTime2, aircraft2.getTailNumber());

        // Search flights
        List<Flight> searchResults = airlineManagementSystem.searchFlights("New York", "London", LocalDate.now().plusDays(1));
        System.out.println("Search Results:");
        for (Flight flight : searchResults) {
            System.out.println("Flight: " + flight.getFlightNumber() + " - " + flight.getSource() + " to " + flight.getDestination());
        }

        // Book a flight
        Booking booking = airlineManagementSystem.bookFlight(flight1.getFlightNumber(), passenger1.getId(), new Seat("25A", SeatType.ECONOMY), 100);
        if (booking != null) {
            System.out.println("Booking successful. Booking ID: " + booking.getId());
        } else {
            System.out.println("Booking failed.");
        }

        // Cancel a booking
        airlineManagementSystem.cancelBooking(booking.getId());
        System.out.println("Booking cancelled.");
    }
}
