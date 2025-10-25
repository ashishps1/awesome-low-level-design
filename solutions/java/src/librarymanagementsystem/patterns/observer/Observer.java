package librarymanagementsystem.patterns.observer;

/**
 * Observer interface for notification system.
 * Part of Observer Design Pattern
 */
public interface Observer {
    void update(String message);
    String getObserverId();
}