package linkedin.observer;

import linkedin.entities.Notification;

import java.util.ArrayList;
import java.util.List;

public abstract class Subject {
    private final List<NotificationObserver> observers = new ArrayList<>();

    public void addObserver(NotificationObserver observer) {
        observers.add(observer);
    }

    public void removeObserver(NotificationObserver observer) {
        observers.remove(observer);
    }

    public void notifyObservers(Notification notification) {
        for (NotificationObserver observer : observers) {
            observer.update(notification);
        }
    }
}
