package onlinestockbrokeragesystem.strategy;

import onlinestockbrokeragesystem.entities.Order;

public interface ExecutionStrategy {
    boolean canExecute(Order order, double marketPrice);
}
