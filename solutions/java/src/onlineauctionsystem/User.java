package onlineauctionsystem;

public class User {
    private final String id;
    private final String username;
    private final String email;

    public User(String id, String username, String email) {
        this.id = id;
        this.username = username;
        this.email = email;
    }

    // Getters and setters

    public String getId() {
        return id;
    }
}
