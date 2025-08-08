package onlineshoppingservice.models;

public class Account {
    private final String username;
    private final String password; // Hashed password in real system
    private final ShoppingCart cart;

    public Account(String username, String password) {
        this.username = username;
        this.password = password;
        this.cart = new ShoppingCart();
    }
    public ShoppingCart getCart() { return cart; }
}
