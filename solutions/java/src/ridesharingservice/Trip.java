package ridesharingservice;

import ridesharingservice.payment.PaymentStatus;

import java.util.UUID;

public class Trip {
    private final String id;
    private Driver driver;
    private final Rider rider;
    private final Location origin;
    private final Location destination;
    private TripStatus status;
    private PaymentStatus paymentStatus;
    private double fare;

    public Trip(Rider rider, Location origin, Location destination) {
        this.id = UUID.randomUUID().toString();
        this.rider = rider;
        this.origin = origin;
        this.destination = destination;
        this.status = TripStatus.REQUESTED;
        this.paymentStatus = PaymentStatus.PENDING;
    }

    public void complete() {
        this.status = TripStatus.COMPLETED;
    }

    public void markPayment() {
        this.paymentStatus = PaymentStatus.COMPLETED;
    }

    public void assignDriver(Driver driver) {
        this.driver = driver;
    }

    public void setStatus(TripStatus status) {
        this.status = status;
    }

    public void setFare(double fare) {
        this.fare = fare;
    }

    public String getId() {
        return id;
    }

    public Rider getRider() {
        return rider;
    }

    public Driver getDriver() {
        return driver;
    }

    public Location getOrigin() {
        return origin;
    }

    public Location getDestination() {
        return destination;
    }

    public TripStatus getStatus() {
        return status;
    }

    public double getFare() {
        return fare;
    }
}
