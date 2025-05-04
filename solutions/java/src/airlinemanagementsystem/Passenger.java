package airlinemanagementsystem;

import java.util.UUID;

public class Passenger {
    private final String id;
    private final String name;
    private final String email;

    public Passenger(String name, String email) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.email = email;
    }

    public String getId() {
        return id;
    }
}
