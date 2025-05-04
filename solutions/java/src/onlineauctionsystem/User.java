package onlineauctionsystem;

public class User {
    private final String username;
    private final String name;

    public User(String username, String name) {
        this.username = username;
        this.name = name;
    }

    public String getUsername() {
        return username;
    }
}
