package ridesharingservice;

public class Ride {
    private final int id;
    private final Passenger passenger;
    private Driver driver;
    private final Location source;
    private final Location destination;
    private RideStatus status;
    private double fare;

    public Ride(int id, Passenger passenger, Driver driver, Location source, Location destination, RideStatus status, double fare) {
        this.id = id;
        this.passenger = passenger;
        this.driver = driver;
        this.source = source;
        this.destination = destination;
        this.status = status;
        this.fare = fare;
    }

    public void setDriver(Driver driver) {
        this.driver = driver;
    }

    public void setStatus(RideStatus status) {
        this.status = status;
    }

    public void setFare(double fare) {
        this.fare = fare;
    }

    public int getId() {
        return id;
    }

    public Passenger getPassenger() {
        return passenger;
    }

    public Driver getDriver() {
        return driver;
    }

    public Location getSource() {
        return source;
    }

    public Location getDestination() {
        return destination;
    }

    public RideStatus getStatus() {
        return status;
    }

    public double getFare() {
        return fare;
    }
}
