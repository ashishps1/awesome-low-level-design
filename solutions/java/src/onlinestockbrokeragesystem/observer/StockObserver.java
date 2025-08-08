package onlinestockbrokeragesystem.observer;

import onlinestockbrokeragesystem.entities.Stock;

public interface StockObserver {
    void update(Stock stock);
}
