package taskmanagementsystem.observer;

import taskmanagementsystem.models.Task;

public interface TaskObserver {
    void update(Task task, String changeType);
}
