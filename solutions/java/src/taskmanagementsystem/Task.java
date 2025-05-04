package taskmanagementsystem;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Task {
    private final String id;
    private String title;
    private String description;
    private Date dueDate;
    private TaskStatus status;
    private TaskPriority priority;
    private User assignee;
    private final List<Comment> comments;
    private final List<Task> subtasks;

    public Task(String id, String title, String description, Date dueDate, TaskPriority priority, User assignee) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
        this.status = TaskStatus.TODO;
        this.assignee = assignee;
        this.comments = new ArrayList<>();
        this.subtasks = new ArrayList<>();
    }

    public synchronized void assignUser(User user) {
        this.assignee = user;
    }

    public synchronized void updateStatus(TaskStatus status) {
        this.status = status;
    }

    public synchronized void updatePriority(TaskPriority priority) {
        this.priority = priority;
    }

    public synchronized void addComment(Comment comment) {
        comments.add(comment);
    }

    public synchronized void addSubtask(Task subtask) {
        subtasks.add(subtask);
    }

    // Getters and setters
    public String getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public TaskPriority getPriority() {
        return priority;
    }

    public Date getDueDate() {
        return dueDate;
    }

    public TaskStatus getStatus() {
        return status;
    }

    public User getAssignee() {
        return assignee;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setDueDate(Date dueDate) {
        this.dueDate = dueDate;
    }

    public void setPriority(TaskPriority priority) {
        this.priority = priority;
    }

    public void setStatus(TaskStatus status) {
        this.status = status;
    }
}
