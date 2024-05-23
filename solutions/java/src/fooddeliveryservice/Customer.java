package fooddeliveryservice;

public class Customer {
    private final String id;
    private final String name;
    private final String email;
    private final String phone;

    public Customer(String id, String name, String email, String phone) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.phone = phone;
    }

    public String getId() {
        return id;
    }
}
