package carrentalsystem;

public class Customer {
    private final String name;
    private final String contactInfo;
    private final String driversLicenseNumber;

    public Customer(String name, String contactInfo, String driversLicenseNumber) {
        this.name = name;
        this.contactInfo = contactInfo;
        this.driversLicenseNumber = driversLicenseNumber;
    }
}
