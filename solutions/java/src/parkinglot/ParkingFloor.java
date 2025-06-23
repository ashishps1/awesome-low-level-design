package parkinglot;

import parkinglot.vehicletype.VehicleType;

import java.util.List;
import java.util.Optional;

public class ParkingFloor {
    private final int floorNumber;
    private final List<ParkingSpot> parkingSpots;

    /**
     * Exp PL 02 :
     * final tells that this list cannot be reassigned after construction. This is good.
     * the only time the contents will change is during construction. In No wy will parkingSpots increase or decrease
     * What this would mean is getAvailableSpot should not be synchronized. Since the concurrency is handled at the parking lot level
     * No need to resync getAvailableSpot.
     */

    public ParkingFloor(int floorNumber, List<ParkingSpot> spots) {
        this.floorNumber = floorNumber;
        this.parkingSpots = spots;
    }

    public Optional<ParkingSpot> getAvailableSpot(VehicleType type) {
        return parkingSpots.stream()
                .filter(spot -> spot.isAvailable() && spot.getVehicleType() == type)
                .findFirst();
    }

    public int getFloorNumber() { return floorNumber; }

    public List<ParkingSpot> getParkingSpots() {
        return parkingSpots;
    }

    public List<Integer> getAvailableSpots(VehicleType type) {
        return parkingSpots.stream()
                .filter(spot -> spot.isAvailable() && spot.getVehicleType() == type)
                .map(ParkingSpot::getSpotNumber)
                .toList();
    }
}
