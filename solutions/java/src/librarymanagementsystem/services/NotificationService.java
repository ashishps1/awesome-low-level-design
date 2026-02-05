package librarymanagementsystem.services;

import librarymanagementsystem.patterns.observer.Observer;
import librarymanagementsystem.patterns.observer.Subject;
import java.util.ArrayList;
import java.util.List;

/**
 * Service for sending notifications to patrons.
 * Follows SRP - Only handles notification logic
 * Implements Observer Pattern for book availability notifications
 */
public class NotificationService implements Subject {
    private final List<Observer> observers;
    
    public NotificationService() {
        this.observers = new ArrayList<>();
    }
    
    /**
     * Send a simple notification (email/SMS simulation).
     */
    public void sendNotification(String recipient, String message) {
        System.out.println("📧 Notification to " + recipient + ": " + message);
        // In real system: integrate with email/SMS service
    }
    
    /**
     * Send notification to multiple recipients.
     */
    public void sendBulkNotification(List<String> recipients, String message) {
        for (String recipient : recipients) {
            sendNotification(recipient, message);
        }
    }
    
    // Observer Pattern implementation
    @Override
    public void attach(Observer observer) {
        if (!observers.contains(observer)) {
            observers.add(observer);
            System.out.println("👤 Observer attached: " + observer.getObserverId());
        }
    }
    
    @Override
    public void detach(Observer observer) {
        observers.remove(observer);
        System.out.println("👤 Observer detached: " + observer.getObserverId());
    }
    
    @Override
    public void notifyObservers(String message) {
        System.out.println("📢 Notifying " + observers.size() + " observers...");
        for (Observer observer : observers) {
            observer.update(message);
        }
    }
    
    /**
     * Notify about book availability.
     */
    public void notifyBookAvailable(String bookTitle) {
        String message = "Good news! The book '" + bookTitle + "' is now available for checkout.";
        notifyObservers(message);
    }
}