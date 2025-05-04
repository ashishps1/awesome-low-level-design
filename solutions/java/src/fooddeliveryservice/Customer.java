package fooddeliveryservice;

import java.util.UUID;

public class Customer {
    private final String id;
    private final String name;
    private final String email;
    private final String phone;

    public Customer(String name, String email, String phone) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.email = email;
        this.phone = phone;
    }

    public String getId() {
        return id;
    }
}
