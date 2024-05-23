package parkinglot;

public class ParkingSpot {
    private int spotNumber;
    private VehicleType vehicleType;
    private Vehicle parkedVehicle;

    public ParkingSpot(int spotNumber) {
        this.spotNumber = spotNumber;
        this.vehicleType = VehicleType.CAR; // Default vehicle type is CAR
    }

    public synchronized boolean isAvailable() {
        return parkedVehicle == null;
    }

    public synchronized void parkVehicle(Vehicle vehicle) {
        if (isAvailable() && vehicle.getType() == vehicleType) {
            parkedVehicle = vehicle;
        } else {
            throw new IllegalArgumentException("Invalid vehicle type or spot already occupied.");
        }
    }

    public synchronized void unparkVehicle() {
        parkedVehicle = null;
    }

    public VehicleType getVehicleType() {
        return vehicleType;
    }

    public Vehicle getParkedVehicle() {
        return parkedVehicle;
    }

    public int getSpotNumber() {
        return spotNumber;
    }
}
