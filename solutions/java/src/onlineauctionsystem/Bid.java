package onlineauctionsystem;

import java.time.LocalDateTime;
import java.util.UUID;

public class Bid {
    private final String id;
    private final User bidder;
    private final double amount;
    private final LocalDateTime timestamp;

    public Bid(User bidder, double amount) {
        this.id = UUID.randomUUID().toString();
        this.bidder = bidder;
        this.amount = amount;
        this.timestamp = LocalDateTime.now();
    }

    public double getAmount() {
        return amount;
    }

    public User getBidder() {
        return bidder;
    }
}
