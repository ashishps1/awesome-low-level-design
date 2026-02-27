package librarymanagementsystem.patterns.observer;

import java.util.ArrayList;
import java.util.List;

/**
 * Subject interface for notification system.
 * Part of Observer Design Pattern
 */
public interface Subject {
    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObservers(String message);
}