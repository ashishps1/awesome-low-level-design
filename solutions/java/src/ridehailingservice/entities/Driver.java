package ridehailingservice.entities;

import ridehailingservice.enums.DriverStatus;
import ridehailingservice.enums.TripStatus;

public class Driver extends User {
    private Vehicle vehicle;
    private Location currentLocation;
    private DriverStatus status;

    public Driver(String name, String contact, Vehicle vehicle, Location initialLocation) {
        super(name, contact);
        this.vehicle = vehicle;
        this.currentLocation = initialLocation;
        this.status = DriverStatus.OFFLINE; // Default status
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public DriverStatus getStatus() {
        return status;
    }

    public void setStatus(DriverStatus status) {
        this.status = status;
        System.out.println("Driver " + getName() + " is now " + status);
    }

    public Location getCurrentLocation() {
        return currentLocation;
    }

    public void setCurrentLocation(Location currentLocation) {
        this.currentLocation = currentLocation;
    }

    @Override public void onUpdate(Trip trip) {
        System.out.printf("--- Notification for Driver %s ---\n", getName());
        System.out.printf("  Trip %s status: %s.\n", trip.getId(), trip.getStatus());
        if (trip.getStatus() == TripStatus.REQUESTED) {
            System.out.println("  A new ride is available for you to accept.");
        }
        System.out.println("--------------------------------\n");
    }
}
