package airlinemanagementsystem.booking;

import airlinemanagementsystem.flight.Flight;
import airlinemanagementsystem.Passenger;
import airlinemanagementsystem.seat.Seat;

import java.util.UUID;

public class Booking {
    private final String id;
    private final Flight flight;
    private final Passenger passenger;
    private final Seat seat;
    private final double price;
    private BookingStatus status;

    public Booking(Flight flight, Passenger passenger, Seat seat, double price) {
        this.id = UUID.randomUUID().toString();
        this.flight = flight;
        this.passenger = passenger;
        this.seat = seat;
        this.price = price;
        this.status = BookingStatus.CONFIRMED;
    }

    public void cancel() {
        status = BookingStatus.CANCELLED;
        seat.release();
    }

    public String getId() {
        return id;
    }
}