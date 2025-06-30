package taskmanagementsystem;

import taskmanagementsystem.sortingstrategy.TaskSortingStrategy;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class TaskManagementSystem {
    private static TaskManagementSystem instance;
    private final Map<String, User> users;
    private final Map<String, Task> tasks;
    private final Map<String, TaskList> taskLists;

    private TaskManagementSystem() {
        users = new ConcurrentHashMap<>();
        tasks = new ConcurrentHashMap<>();
        taskLists = new ConcurrentHashMap<>();
    }

    public static synchronized TaskManagementSystem getInstance() {
        if (instance == null) {
            instance = new TaskManagementSystem();
        }
        return instance;
    }

    public User createUser(String name, String email) {
        User user = new User(name, email);
        users.put(user.getId(), user);
        return user;
    }

    public TaskList createTaskList(String listName) {
        TaskList taskList = new TaskList(listName);
        taskLists.put(taskList.getId(), taskList);
        return taskList;
    }

    public Task createTask(String listId, String title, String description, Date dueDate,
                           TaskPriority priority, String createdByUserId) {
        TaskList taskList = taskLists.get(listId);
        if (taskList == null) throw new IllegalArgumentException("TaskList not found.");

        User createdBy = users.get(createdByUserId);
        if (createdBy == null) throw new IllegalArgumentException("User not found.");

        Task task = new Task(title, description, dueDate, priority, createdBy);

        tasks.put(task.getId(), task);
        taskList.addTask(task);
        return task;
    }

    public Task getTaskById(String taskId) {
        if (!tasks.containsKey(taskId)) {
            throw new RuntimeException("Task not found: " + taskId);
        }
        return tasks.get(taskId);
    }

    public void updateTaskStatus(String taskId, TaskStatus status) {
        getTaskById(taskId).updateStatus(status);
    }

    public void updateTaskPriority(String taskId, TaskPriority priority) {
        getTaskById(taskId).updatePriority(priority);
    }

    public void assignTask(String taskId, String userId) {
        User user = users.get(userId);
        if (user == null) throw new IllegalArgumentException("User not found.");
        getTaskById(taskId).assignUser(user);
    }

    public void addComment(String taskId, String commentText, User author) {
        Task task = getTaskById(taskId);
        task.addComment(new Comment(commentText, author));
    }

    public List<Task> listTasksByUser(String userId) {
        User user = users.get(userId);
        return tasks.values().stream()
                .filter(task -> user.equals(task.getAssignedTo()))
                .toList();
    }

    public List<Task> listTasksByStatus(TaskStatus status) {
        return tasks.values().stream()
                .filter(task -> task.getStatus() == status)
                .collect(Collectors.toList());
    }

    public void deleteTask(String taskId) {
        tasks.remove(taskId);
    }

    public List<Task> searchTasks(String keyword, TaskSortingStrategy sortingStrategy) {
        List<Task> matchingTasks = new ArrayList<>();
        for (Task task : tasks.values()) {
            if (task.getTitle().contains(keyword) || task.getDescription().contains(keyword)) {
                matchingTasks.add(task);
            }
        }
        sortingStrategy.sort(matchingTasks);
        return matchingTasks;
    }
}
