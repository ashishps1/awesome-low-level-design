package onlineauctionsystem.observer;

import onlineauctionsystem.entities.Auction;

public interface AuctionObserver {
    void onUpdate(Auction auction, String message);
}
