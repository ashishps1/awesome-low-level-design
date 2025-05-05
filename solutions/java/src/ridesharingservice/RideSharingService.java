package ridesharingservice;

import ridesharingservice.payment.Payment;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class RideSharingService {
    private static RideSharingService instance;
    private final Map<String, Driver> drivers;
    private final Map<String, Rider> riders;
    private final Map<String, Trip> trips;

    private RideSharingService() {
        riders = new ConcurrentHashMap<>();
        drivers = new ConcurrentHashMap<>();
        trips = new ConcurrentHashMap<>();
    }

    public static synchronized RideSharingService getInstance() {
        if (instance == null) {
            instance = new RideSharingService();
        }
        return instance;
    }

    public Driver registerDriver(String name, String contact, String licensePlate, Location location) {
        Driver driver = new Driver(name, contact, licensePlate, location);
        drivers.put(driver.getId(), driver);
        return driver;
    }

    public Rider registerRider(String name, String contact) {
        Rider rider = new Rider(name, contact);
        riders.put(rider.getId(), rider);
        return rider;
    }

    public void updateDriverLocation(String driverId, Location location) {
        Driver driver = drivers.get(driverId);
        if (driver != null) {
            driver.updateLocation(location);
        } else {
            throw new IllegalArgumentException("Driver not found");
        }
    }

    public synchronized Trip requestRide(String riderId, Location from, Location to) {
        Rider rider = riders.get(riderId);
        if (rider == null) throw new IllegalArgumentException("Rider not found");

        Trip trip = new Trip(rider, from, to);

        notifyNearbyDrivers(trip);

        trips.put(trip.getId(), trip);
        return trip;
    }

    public void acceptRide(String driverId, String tripId) {
        Driver driver = drivers.get(driverId);
        Trip trip = trips.get(tripId);
        if (trip.getStatus() == TripStatus.REQUESTED) {
            Rider rider = trip.getRider();
            trip.assignDriver(driver);
            trip.setStatus(TripStatus.ACCEPTED);
            driver.setStatus(DriverStatus.BUSY);
            rider.assignTrip(trip);
            System.out.printf("Trip started: %s (Driver: %s -> Rider: %s)%n",
                    trip.getId(), driver.getName(), rider.getName());
            notifyRider(trip);
        }
    }

    public void startRide(String tripId) {
        Trip trip = trips.get(tripId);
        if (trip.getStatus() == TripStatus.ACCEPTED) {
            trip.setStatus(TripStatus.ONGOING);
            notifyRider(trip);
        }
    }

    public synchronized void completeRide(String tripId) {
        Trip trip = trips.get(tripId);
        if (trip.getStatus() == TripStatus.ONGOING) {
            trip.complete();
            trip.getDriver().completeTrip();
            trip.getRider().completeTrip();

            double fare = calculateFare(trip);
            trip.setFare(fare);

            notifyRider(trip);
            notifyDriver(trip);
            System.out.printf("Trip %s completed%n", trip.getId());
        }
    }

    public void cancelRide(String tripId) {
        Trip trip = trips.get(tripId);
        if (trip.getStatus() == TripStatus.REQUESTED || trip.getStatus() == TripStatus.ACCEPTED) {
            trip.setStatus(TripStatus.CANCELLED);
            if (trip.getDriver() != null) {
                trip.getDriver().setStatus(DriverStatus.AVAILABLE);
            }
            notifyDriver(trip);
        }
    }

    public void makePayment(String tripId, Payment payment) {
        Trip trip = trips.get(tripId);
        double fare = trip.getFare();
        payment.processPayment(fare);
        trip.markPayment();
    }

    private void notifyNearbyDrivers(Trip trip) {
        boolean foundNearbyAvailableDriver = false;
        for (Driver driver : drivers.values()) {
            if (driver.isAvailable()) {
                double distance = trip.getOrigin().distanceTo(driver.getLocation());
                if (distance <= 15.0) { // Notify drivers within 5 km radius
                    foundNearbyAvailableDriver = true;
                    // Send notification to the driver
                    System.out.println("Notifying driver: " + driver.getName() + " about ride request: " + trip.getId());
                }
            }
        }

        if(!foundNearbyAvailableDriver) {
            throw new IllegalStateException("No available drivers");
        }
    }

    private void notifyRider(Trip trip) {
        // Notify the passenger about ride status updates
        // ...
        User user = trip.getRider();
        String message = switch (trip.getStatus()) {
            case ACCEPTED -> "Your ride has been accepted by driver: " + trip.getDriver().getName();
            case ONGOING -> "Your ride is in progress";
            case COMPLETED -> "Your ride has been completed. Fare: $" + trip.getFare();
            case CANCELLED -> "Your ride has been cancelled";
            default -> "";
        };
        // Send notification to the passenger
        System.out.println("Notifying rider: " + user.getName() + " - " + message);
    }

    private void notifyDriver(Trip trip) {
        Driver driver = trip.getDriver();
        if (driver != null) {
            String message = switch (trip.getStatus()) {
                case COMPLETED -> "Ride completed. Fare: $" + trip.getFare();
                case CANCELLED -> "Ride cancelled by passenger";
                default -> "";
            };
            // Send notification to the driver
            System.out.println("Notifying driver: " + driver.getName() + " - " + message);
        }
    }

    private double calculateFare(Trip trip) {
        double baseFare = 2.0;
        double perKmFare = 1.5;

        double distance = trip.getOrigin().distanceTo(trip.getDestination());

        double fare = baseFare + (distance * perKmFare);
        return Math.round(fare * 100.0) / 100.0; // Round to 2 decimal places
    }
}
