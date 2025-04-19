package parkinglot;

import parkinglot.vehicletype.Vehicle;
import parkinglot.vehicletype.VehicleType;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Level {
    private final int floor;
    private final List<ParkingSpot> parkingSpots;
    private AtomicInteger availableSpots;

    public Level(int floor, int numSpots) {
        this.floor = floor;
        availableSpots = new AtomicInteger(numSpots);
        parkingSpots = new ArrayList<>(numSpots);
        // Assign spots in ration of 50:40:10 for bikes, cars and trucks
        double spotsForBikes = 0.50;
        double spotsForCars = 0.40;

        int numBikes = (int) (numSpots * spotsForBikes);
        int numCars = (int) (numSpots * spotsForCars);

        for (int i = 1; i <= numBikes; i++) {
            parkingSpots.add(new ParkingSpot(i,VehicleType.MOTORCYCLE));
        }
        for (int i = numBikes + 1; i <= numBikes + numCars; i++) {
            parkingSpots.add(new ParkingSpot(i,VehicleType.CAR));
        }
        for (int i = numBikes + numCars + 1; i <= numSpots; i++) {
            parkingSpots.add(new ParkingSpot(i,VehicleType.TRUCK));
        }
    }

    public synchronized Ticket parkVehicle(Vehicle vehicle) {
        for (ParkingSpot spot : parkingSpots) {
            if (spot.isAvailable() && spot.getVehicleType() == vehicle.getType()) {
                spot.parkVehicle(vehicle);
                availableSpots.incrementAndGet();
                Ticket ticket = new Ticket(vehicle, spot.getSpotNumber(), floor, java.time.LocalDateTime.now());
                return TicketManager.getTicket(ticket);
            }
        }
        return null;
    }

    public int getAvailableSpots() {
        return availableSpots.get();
    }

    public synchronized boolean unparkVehicle(Vehicle vehicle) {
        for (ParkingSpot spot : parkingSpots) {
            if (!spot.isAvailable() && spot.getParkedVehicle().equals(vehicle)) {
                spot.unparkVehicle();
                availableSpots.decrementAndGet();
                return true;
            }
        }
        return false;
    }

    public void displayAvailability() {
        System.out.println("Level " + floor + " Availability:");
        for (ParkingSpot spot : parkingSpots) {
            System.out.println("Spot " + spot.getSpotNumber() + ": " + (spot.isAvailable() ? "Available For"  : "Occupied By ")+" "+spot.getVehicleType());
        }
    }
}