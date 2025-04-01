package stackoverflow;

public class Vote {
    private final User user;
    private final int value;

    public Vote(User user, int value) {
        this.user = user;
        this.value = value;
    }

    // Getters
    public User getUser() { return user; }
    public int getValue() { return value; }
}
