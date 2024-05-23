package onlineshopping;

import java.util.ArrayList;
import java.util.List;

public class User {
    private final String id;
    private final String name;
    private final String email;
    private final String password;
    private final List<Order> orders;

    public User(String id, String name, String email, String password) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.password = password;
        this.orders = new ArrayList<>();
    }

    public void addOrder(Order order) {
        orders.add(order);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public List<Order> getOrders() {
        return orders;
    }
}
