package ridesharingservice;

public class Driver {
    private int id;
    private String name;
    private String contact;
    private String licensePlate;
    private Location location;
    private DriverStatus status;

    public Driver(int id, String name, String contact, String licensePlate, Location location, DriverStatus status) {
        this.id = id;
        this.name = name;
        this.contact = contact;
        this.licensePlate = licensePlate;
        this.location = location;
        this.status = status;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setContact(String contact) {
        this.contact = contact;
    }

    public void setLicensePlate(String licensePlate) {
        this.licensePlate = licensePlate;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public void setStatus(DriverStatus status) {
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getContact() {
        return contact;
    }

    public String getLicensePlate() {
        return licensePlate;
    }

    public Location getLocation() {
        return location;
    }

    public DriverStatus getStatus() {
        return status;
    }
}
