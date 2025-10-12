package onlineshoppingservice.observer;

import onlineshoppingservice.models.Order;

import java.util.ArrayList;
import java.util.List;

public abstract class Subject {
    private final List<OrderObserver> observers = new ArrayList<>();

    public void addObserver(OrderObserver observer) { observers.add(observer); }
    public void removeObserver(OrderObserver observer) { observers.remove(observer); }
    public void notifyObservers(Order order) {
        for (OrderObserver observer : observers) {
            observer.update(order);
        }
    }
}
