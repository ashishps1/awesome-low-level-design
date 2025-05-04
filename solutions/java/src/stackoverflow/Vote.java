package stackoverflow;

public class Vote {
    private final User voter;
    private final VoteType type;

    public Vote(User user, VoteType type) {
        this.voter = user;
        this.type = type;
    }

    // Getters
    public User getVoter() { return voter; }
    public VoteType getType() { return type; }
}
