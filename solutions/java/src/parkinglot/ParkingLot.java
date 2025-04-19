package parkinglot;

import parkinglot.vehicletype.Vehicle;

import java.util.ArrayList;
import java.util.List;

public class ParkingLot {
    private static ParkingLot instance;
    private final List<Level> levels;

    private ParkingLot() {
        levels = new ArrayList<>();
    }

    public static synchronized ParkingLot getInstance() {
        if (instance == null) {
            instance = new ParkingLot();
        }
        return instance;
    }

    public void addLevel(Level level) {
        levels.add(level);
    }

    public Ticket parkVehicle(Vehicle vehicle) {
        for (Level level : levels) {
            if (level.getAvailableSpots() > 0) {
                Ticket ticket = level.parkVehicle(vehicle);
                if (ticket == null) {
                    continue; // No available spot in this level
                }
                System.out.println("Vehicle parked successfully.");
                return ticket;
            }
        }
        System.out.println("Could not park vehicle.");
        return null;
    }

    public boolean unparkVehicle(Vehicle vehicle) {
        for (Level level : levels) {
            if (level.unparkVehicle(vehicle)) {
                return true;
            }
        }
        return false;
    }

    public void displayAvailability() {
        for (Level level : levels) {
            level.displayAvailability();
        }
    }
}
