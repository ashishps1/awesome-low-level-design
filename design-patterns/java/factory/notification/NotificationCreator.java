public abstract class NotificationCreator {
    // Factory Method
    public abstract Notification createNotification();
    
    // Common logic using the factory method
    public void send(String message) {
        Notification notification = createNotification();
        notification.send(message);
    }
}