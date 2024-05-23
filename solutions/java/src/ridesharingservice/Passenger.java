package ridesharingservice;

public class Passenger {
    private int id;
    private String name;
    private String contact;
    private Location location;

    public Passenger(int id, String name, String contact, Location location) {
        this.id = id;
        this.name = name;
        this.contact = contact;
        this.location = location;
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

    public Location getLocation() {
        return location;
    }
}
