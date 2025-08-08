package linkedin.observer;

import linkedin.entities.Notification;

public interface NotificationObserver {
    void update(Notification notification);
}
