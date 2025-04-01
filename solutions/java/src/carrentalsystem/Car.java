package carrentalsystem;

public class Car {
    private final String make;
    private final String model;
    private final int year;
    private final String licensePlate;
    private final double rentalPricePerDay;
    private boolean available;

    public Car(String make, String model, int year, String licensePlate, double rentalPricePerDay) {
        this.make = make;
        this.model = model;
        this.year = year;
        this.licensePlate = licensePlate;
        this.rentalPricePerDay = rentalPricePerDay;
        this.available = true;
    }

    public double getRentalPricePerDay() {
        return rentalPricePerDay;
    }

    public String getLicensePlate() {
        return licensePlate;
    }

    public String getMake() {
        return make;
    }

    public String getModel() {
        return model;
    }

    public boolean isAvailable() {
        return available;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }
}
