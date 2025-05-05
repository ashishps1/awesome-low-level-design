package ridesharingservice;

import java.util.UUID;

public abstract class User {
    private final String id;
    private final String name;
    private final String contact;

    public User(String name, String contact) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.contact = contact;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getContact() {
        return contact;
    }
}
