package ridesharingservice;

import java.util.Map;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class RideService {
    private static RideService instance;
    private final Map<Integer, Passenger> passengers;
    private final Map<Integer, Driver> drivers;
    private final Map<Integer, Ride> rides;
    private final Queue<Ride> requestedRides;

    private RideService() {
        passengers = new ConcurrentHashMap<>();
        drivers = new ConcurrentHashMap<>();
        rides = new ConcurrentHashMap<>();
        requestedRides = new ConcurrentLinkedQueue<>();
    }

    public static synchronized RideService getInstance() {
        if (instance == null) {
            instance = new RideService();
        }
        return instance;
    }

    public void addPassenger(Passenger passenger) {
        passengers.put(passenger.getId(), passenger);
    }

    public void addDriver(Driver driver) {
        drivers.put(driver.getId(), driver);
    }

    public void requestRide(Passenger passenger, Location source, Location destination) {
        Ride ride = new Ride(generateRideId(), passenger, null, source, destination, RideStatus.REQUESTED, 0.0);
        requestedRides.offer(ride);
        notifyDrivers(ride);
    }

    public void acceptRide(Driver driver, Ride ride) {
        if (ride.getStatus() == RideStatus.REQUESTED) {
            ride.setDriver(driver);
            ride.setStatus(RideStatus.ACCEPTED);
            driver.setStatus(DriverStatus.BUSY);
            notifyPassenger(ride);
        }
    }

    public void startRide(Ride ride) {
        if (ride.getStatus() == RideStatus.ACCEPTED) {
            ride.setStatus(RideStatus.IN_PROGRESS);
            notifyPassenger(ride);
        }
    }

    public void completeRide(Ride ride) {
        if (ride.getStatus() == RideStatus.IN_PROGRESS) {
            ride.setStatus(RideStatus.COMPLETED);
            ride.getDriver().setStatus(DriverStatus.AVAILABLE);
            double fare = calculateFare(ride);
            ride.setFare(fare);
            processPayment(ride, fare);
            notifyPassenger(ride);
            notifyDriver(ride);
        }
    }

    public void cancelRide(Ride ride) {
        if (ride.getStatus() == RideStatus.REQUESTED || ride.getStatus() == RideStatus.ACCEPTED) {
            ride.setStatus(RideStatus.CANCELLED);
            if (ride.getDriver() != null) {
                ride.getDriver().setStatus(DriverStatus.AVAILABLE);
            }
            notifyPassenger(ride);
            notifyDriver(ride);
        }
    }

    private void notifyDrivers(Ride ride) {
        for (Driver driver : drivers.values()) {
            if (driver.getStatus() == DriverStatus.AVAILABLE) {
                double distance = calculateDistance(driver.getLocation(), ride.getSource());
                if (distance <= 5.0) { // Notify drivers within 5 km radius
                    // Send notification to the driver
                    System.out.println("Notifying driver: " + driver.getName() + " about ride request: " + ride.getId());
                }
            }
        }
    }

    private void notifyPassenger(Ride ride) {
        // Notify the passenger about ride status updates
        // ...
        Passenger passenger = ride.getPassenger();
        String message = "";
        switch (ride.getStatus()) {
            case ACCEPTED:
                message = "Your ride has been accepted by driver: " + ride.getDriver().getName();
                break;
            case IN_PROGRESS:
                message = "Your ride is in progress";
                break;
            case COMPLETED:
                message = "Your ride has been completed. Fare: $" + ride.getFare();
                break;
            case CANCELLED:
                message = "Your ride has been cancelled";
                break;
        }
        // Send notification to the passenger
        System.out.println("Notifying passenger: " + passenger.getName() + " - " + message);
    }

    private void notifyDriver(Ride ride) {
        Driver driver = ride.getDriver();
        if (driver != null) {
            String message = "";
            switch (ride.getStatus()) {
                case COMPLETED:
                    message = "Ride completed. Fare: $" + ride.getFare();
                    break;
                case CANCELLED:
                    message = "Ride cancelled by passenger";
                    break;
            }
            // Send notification to the driver
            System.out.println("Notifying driver: " + driver.getName() + " - " + message);
        }
    }

    private double calculateFare(Ride ride) {
        double baseFare = 2.0;
        double perKmFare = 1.5;
        double perMinuteFare = 0.25;

        double distance = calculateDistance(ride.getSource(), ride.getDestination());
        double duration = calculateDuration(ride.getSource(), ride.getDestination());

        double fare = baseFare + (distance * perKmFare) + (duration * perMinuteFare);
        return Math.round(fare * 100.0) / 100.0; // Round to 2 decimal places
    }

    public double calculateDistance(Location source, Location Destination) {
        // Calculate the distance between two locations using a distance formula (e.g., Haversine formula)
        // For simplicity, let's assume a random distance between 1 and 20 km
        return Math.random() * 20 + 1;
    }

    private double calculateDuration(Location source, Location destination) {
        // Calculate the estimated duration between two locations based on distance and average speed
        // For simplicity, let's assume an average speed of 30 km/h
        double distance = calculateDistance(source, destination);
        return (distance / 30) * 60; // Convert hours to minutes
    }

    private void processPayment(Ride ride, double amount) {
        // Process the payment for the ride
        // ...
    }

    private int generateRideId() {
        return (int) (System.currentTimeMillis() / 1000);
    }

    public Map<Integer, Ride> getRides() {
        return rides;
    }

    public Queue<Ride> getRequestedRides() {
        return requestedRides;
    }
}
