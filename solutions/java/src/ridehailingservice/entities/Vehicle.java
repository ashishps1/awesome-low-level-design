package ridehailingservice.entities;

import ridehailingservice.enums.RideType;

public class Vehicle {
    private final String licenseNumber;
    private final String model;
    private final RideType type;

    public Vehicle(String licenseNumber, String model, RideType type) {
        this.licenseNumber = licenseNumber;
        this.model = model;
        this.type = type;
    }

    public String getLicenseNumber() { return licenseNumber; }

    public String getModel() { return model; }

    public RideType getType() { return type; }
}
