# Designing a Task Management System

In this article, we explore the design and implementation of a Task Management System using Java, with a focus on object-oriented principles. 

The system allows users to create, manage, and track tasks effectively.

## System Requirements

The Task Management System should:

1. **Task Creation and Management**: Enable users to create, update, and delete tasks.
2. **User Management**: Manage user accounts and associated tasks.
3. **Task Assignment**: Allow tasks to be assigned to specific users.
4. **Task Tracking**: Track the progress and status of tasks.
5. **Notifications**: Notify users about task deadlines and updates.

## Core Use Cases

1. **Managing User Accounts**
2. **Creating and Updating Tasks**
3. **Assigning Tasks to Users**
4. **Tracking Task Progress**
5. **Sending Notifications**

## Key Classes:
- `TaskManagementSystem`: Manages the overall system.
- `User`: Represents a system user.
- `Task`: Represents a task.
- `TaskStatus`: Enum for task status.

## Java Implementation

### User Class

Manages user account information.

```java
import java.util.ArrayList;
import java.util.List;

public class User {
    private String userId;
    private String name;
    private List<Task> assignedTasks;

    public User(String userId, String name) {
        this.userId = userId;
        this.name = name;
        this.assignedTasks = new ArrayList<>();
    }

    public void addTask(Task task) {
        assignedTasks.add(task);
    }

    // Getters and setters...
}
```
### Task Class
Represents a task.
```java
import java.util.Date;

public class Task {
    private String taskId;
    private String title;
    private String description;
    private Date dueDate;
    private TaskStatus status;

    public Task(String taskId, String title, Date dueDate) {
        this.taskId = taskId;
        this.title = title;
        this.dueDate = dueDate;
        this.status = TaskStatus.PENDING;
    }

    public void updateStatus(TaskStatus newStatus) {
        this.status = newStatus;
    }

    // Getters and setters...
}

enum TaskStatus {
    PENDING, IN_PROGRESS, COMPLETED, CANCELLED
}
```
### TaskManagementSystem Class
Manages task management operations.
```java
import java.util.ArrayList;
import java.util.List;

public class TaskManagementSystem {
    private List<User> users;
    private List<Task> tasks;

    public TaskManagementSystem() {
        this.users = new ArrayList<>();
        this.tasks = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public void addTask(Task task) {
        tasks.add(task);
    }

    public void assignTaskToUser(String taskId, String userId) {
        User user = findUserById(userId);
        Task task = findTaskById(taskId);

        if (user != null && task != null) {
            user.addTask(task);
        }
    }

    public User findUserById(String userId) {
        for (User user : users) {
            if (user.getUserId().equals(userId)) {
                return user;
            }
        }
        return null;
    }

    public Task findTaskById(String taskId) {
        for (Task task : tasks) {
            if (task.getTaskId().equals(taskId)) {
                return task;
            }
        }
        return null;
    }
```


