package parkinglot.vehicle;

public abstract class Vehicle {
    protected String licensePlate;
    protected VehicleType type;

    public Vehicle(String licensePlate, VehicleType type) {
        this.licensePlate = licensePlate;
        this.type = type;
    }

    public String getLicenseNumber() { return licensePlate; }
    public VehicleType getType() {
        return type;
    }
}
