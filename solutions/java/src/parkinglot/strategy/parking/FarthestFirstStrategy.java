package parkinglot.strategy.parking;

import parkinglot.entities.ParkingFloor;
import parkinglot.entities.ParkingSpot;
import parkinglot.vehicle.Vehicle;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

public class FarthestFirstStrategy implements ParkingStrategy {
    @Override
    public Optional<ParkingSpot> findSpot(List<ParkingFloor> floors, Vehicle vehicle) {
        // Create a reversed copy of the floors list to search from the top floor down.
        List<ParkingFloor> reversedFloors = new ArrayList<>(floors);
        Collections.reverse(reversedFloors);

        for (ParkingFloor floor : reversedFloors) {
            Optional<ParkingSpot> spot = floor.findAvailableSpot(vehicle);
            if (spot.isPresent()) {
                return spot;
            }
        }
        return Optional.empty();
    }
}
