package ridehailingservice.entities;

import ridehailingservice.observer.Rider;
import ridehailingservice.enums.TripStatus;
import ridehailingservice.observer.TripObserver;
import ridehailingservice.state.RequestedState;
import ridehailingservice.state.TripState;

import java.util.UUID;

import java.util.ArrayList;
import java.util.List;

public class Trip {
    private final String id;
    private final Rider rider;
    private Driver driver;
    private final Location pickupLocation;
    private final Location dropoffLocation;
    private final double fare;
    private TripStatus status;

    private TripState currentState;
    private final List<TripObserver> observers = new ArrayList<>();

    private Trip(TripBuilder builder) {
        this.id = builder.id;
        this.rider = builder.rider;
        this.pickupLocation = builder.pickupLocation;
        this.dropoffLocation = builder.dropoffLocation;
        this.fare = builder.fare;
        this.status = TripStatus.REQUESTED;
        this.currentState = new RequestedState(); // Initial state
    }

    public void addObserver(TripObserver observer) {
        observers.add(observer);
    }

    private void notifyObservers() {
        observers.forEach(o -> o.onUpdate(this));
    }

    public void assignDriver(Driver driver) {
        currentState.assign(this, driver);
        addObserver(driver);
        notifyObservers();
    }

    public void startTrip() {
        currentState.start(this);
        notifyObservers();
    }

    public void endTrip() {
        currentState.end(this);
        notifyObservers();
    }

    // Getters
    public String getId() { return id; }
    public Rider getRider() { return rider; }
    public Driver getDriver() { return driver; }
    public Location getPickupLocation() { return pickupLocation; }
    public Location getDropoffLocation() { return dropoffLocation; }
    public double getFare() { return fare; }
    public TripStatus getStatus() { return status; }

    // Setters are protected, only to be called by State objects
    public void setState(TripState state) {
        this.currentState = state;
    }

    public void setStatus(TripStatus status) {
        this.status = status;
    }

    public void setDriver(Driver driver) {
        this.driver = driver;
    }

    // --- Builder Pattern ---
    public static class TripBuilder {
        private final String id;
        private Rider rider;
        private Location pickupLocation;
        private Location dropoffLocation;
        private double fare;

        public TripBuilder() {
            this.id = UUID.randomUUID().toString();
        }

        public TripBuilder withRider(Rider rider) {
            this.rider = rider;
            return this;
        }

        public TripBuilder withPickupLocation(Location pickupLocation) {
            this.pickupLocation = pickupLocation;
            return this;
        }

        public TripBuilder withDropoffLocation(Location dropoffLocation) {
            this.dropoffLocation = dropoffLocation;
            return this;
        }

        public TripBuilder withFare(double fare) {
            this.fare = fare;
            return this;
        }

        public Trip build() {
            // Basic validation
            if (rider == null || pickupLocation == null || dropoffLocation == null) {
                throw new IllegalStateException("Rider, pickup, and dropoff locations are required to build a trip.");
            }
            return new Trip(this);
        }
    }

    @Override
    public String toString() {
        return "Trip [id=" + id + ", status=" + status + ", fare=$" + String.format("%.2f", fare) + "]";
    }
}