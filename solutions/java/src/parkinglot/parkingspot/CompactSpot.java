package parkinglot.parkingspot;

import parkinglot.vehicle.Vehicle;
import parkinglot.vehicle.VehicleType;

public class CompactSpot extends ParkingSpot {
    public CompactSpot(String spotId) {
        super(spotId);
    }

    @Override
    public boolean canFitVehicle(Vehicle vehicle) {
        VehicleType type = vehicle.getType();
        return type == VehicleType.CAR;
    }
}
