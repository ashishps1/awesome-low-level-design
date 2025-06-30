package taskmanagementsystem;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;

public class Task {
    private final String id;
    private String title;
    private String description;
    private Date dueDate;
    private TaskStatus status;
    private TaskPriority priority;
    private final User createdBy;
    private User assignedTo;
    private final List<Comment> comments;
    private final List<Task> subtasks;
    private final List<ActivityLog> history = new ArrayList<>();

    public Task(String title, String description, Date dueDate, TaskPriority priority, User createdBy) {
        this.id = UUID.randomUUID().toString();
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
        this.status = TaskStatus.TODO;
        this.createdBy = createdBy;
        this.comments = new ArrayList<>();
        this.subtasks = new ArrayList<>();
        logActivity("Created");
    }

    public synchronized void assignUser(User user) {
        this.assignedTo = user;
        logActivity("Assigned to " + user.getName());
    }

    public synchronized void updateStatus(TaskStatus status) {
        this.status = status;
        logActivity("Status changed to " + status);
    }

    public synchronized void updatePriority(TaskPriority priority) {
        this.priority = priority;
    }

    public synchronized void addComment(Comment comment) {
        comments.add(comment);
        logActivity("Comment added by " + comment.getAuthor().getName());
    }

    public synchronized void addSubtask(Task subtask) {
        subtasks.add(subtask);
        logActivity("Subtask added: " + subtask.getTitle());
    }

    private void logActivity(String action) {
        history.add(new ActivityLog(action, createdBy));
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

    public User getAssignedTo() {
        return assignedTo;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setStatus(TaskStatus status) {
        this.status = status;
    }
}
