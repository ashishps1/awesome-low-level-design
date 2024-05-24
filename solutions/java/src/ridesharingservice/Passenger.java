package ridesharingservice;

public class Passenger {
    private final int id;
    private final String name;
    private final String contact;
    private final Location location;

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
