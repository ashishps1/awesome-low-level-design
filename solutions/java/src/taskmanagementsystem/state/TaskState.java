package taskmanagementsystem.state;

import taskmanagementsystem.models.Task;
import taskmanagementsystem.enums.TaskStatus;

public interface TaskState {
    void startProgress(Task task);
    void completeTask(Task task);
    void reopenTask(Task task);
    TaskStatus getStatus();
}
