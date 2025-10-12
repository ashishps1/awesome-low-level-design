package onlineauctionsystem.entities;

import onlineauctionsystem.observer.AuctionObserver;

import java.util.UUID;

public class User implements AuctionObserver {
    private final String id;
    private final String name;

    public User(String name) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    @Override
    public void onUpdate(Auction auction, String message) {
        System.out.printf("--- Notification for %s ---\n", this.name);
        System.out.printf("Auction: %s\n", auction.getItemName());
        System.out.printf("Message: %s\n", message);
        System.out.println("---------------------------\n");
    }
}
