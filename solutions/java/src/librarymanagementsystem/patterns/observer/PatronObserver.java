package librarymanagementsystem.patterns.observer;

import librarymanagementsystem.models.Patron;

/**
 * Concrete Observer - Patron receives notifications.
 * Implements Observer Design Pattern
 */
public class PatronObserver implements Observer {
    private final Patron patron;
    
    public PatronObserver(Patron patron) {
        this.patron = patron;
    }
    
    @Override
    public void update(String message) {
        System.out.println("📧 Notification to " + patron.getName() + ": " + message);
        // In real system, send email/SMS here
    }
    
    @Override
    public String getObserverId() {
        return patron.getPatronId();
    }
    
    public Patron getPatron() {
        return patron;
    }
}