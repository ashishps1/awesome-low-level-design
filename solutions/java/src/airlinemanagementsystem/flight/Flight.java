package airlinemanagementsystem.flight;

import airlinemanagementsystem.Aircraft;
import airlinemanagementsystem.seat.Seat;

import java.time.LocalDateTime;
import java.util.*;

public class Flight {
    private final String flightNumber;
    private final String source;
    private final String destination;
    private final LocalDateTime departureTime;
    private final LocalDateTime arrivalTime;
    private final FlightStatus status;
    private final Aircraft aircraft;
    private final Map<String, Seat> seats;
    private final List<Seat> availableSeats;

    public Flight(String source, String destination, LocalDateTime departureTime, LocalDateTime arrivalTime, Aircraft aircraft) {
        this.flightNumber = UUID.randomUUID().toString();
        this.source = source;
        this.destination = destination;
        this.departureTime = departureTime;
        this.arrivalTime = arrivalTime;
        this.status = FlightStatus.ON_TIME;
        this.aircraft = aircraft;
        this.seats = new HashMap<>();
        this.availableSeats = new ArrayList<>();
    }

    public synchronized boolean isSeatAvailable(String seatNo) {
        Seat seat = seats.get(seatNo);
        return seat != null && !seat.isBooked();
    }

    public synchronized void reserveSeat(String seatNo) {
        Seat seat = seats.get(seatNo);
        if (seat == null) throw new IllegalArgumentException("Invalid seat number");
        seat.reserve();
    }

    public synchronized void releaseSeat(String seatNo) {
        Seat seat = seats.get(seatNo);
        if (seat != null) seat.release();
    }

    public String getSource() {
        return source;
    }

    public String getDestination() {
        return destination;
    }

    public LocalDateTime getDepartureTime() {
        return departureTime;
    }

    public String getFlightNumber() {
        return flightNumber;
    }

    public LocalDateTime getArrivalTime() {
        return arrivalTime;
    }

    public List<Seat> getAvailableSeats() {
        return availableSeats;
    }
}
