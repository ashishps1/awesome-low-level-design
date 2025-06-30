package stackoverflow;

import java.util.UUID;

public class User {
    private final String userId;
    private final String name;
    private final String email;
    private int reputation;

    public User(String name, String email) {
        this.userId = UUID.randomUUID().toString();
        this.name = name;
        this.email = email;
        this.reputation = 0;
    }

    public synchronized void updateReputation(int value) {
        this.reputation += value;
        if (this.reputation < 0) {
            this.reputation = 0;
        }
    }

    // Getters
    public String getUserId() { return userId; }
    public String getName() { return name; }
    public int getReputation() { return reputation; }
}