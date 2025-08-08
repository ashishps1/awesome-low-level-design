package onlinestockbrokeragesystem.strategy;

import onlinestockbrokeragesystem.entities.Order;
import onlinestockbrokeragesystem.enums.TransactionType;

public class LimitOrderStrategy implements ExecutionStrategy {
    private final TransactionType type;

    public LimitOrderStrategy(TransactionType type) {
        this.type = type;
    }

    @Override
    public boolean canExecute(Order order, double marketPrice) {
        if (type == TransactionType.BUY) {
            // Buy if market price is less than or equal to limit price
            return marketPrice <= order.getPrice();
        } else { // SELL
            // Sell if market price is greater than or equal to limit price
            return marketPrice >= order.getPrice();
        }
    }
}
