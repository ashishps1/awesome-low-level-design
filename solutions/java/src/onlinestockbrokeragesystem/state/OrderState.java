package onlinestockbrokeragesystem.state;

import onlinestockbrokeragesystem.entities.Order;

public interface OrderState {
    void handle(Order order);
    void cancel(Order order);
}
