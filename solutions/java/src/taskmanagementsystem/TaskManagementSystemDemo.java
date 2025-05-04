package taskmanagementsystem;

import java.util.Date;
import java.util.List;

public class TaskManagementSystemDemo {
    public static void run() {
        TaskManager taskManager = TaskManager.getInstance();

        // Create users
        User user1 = new User("1", "John Doe", "john@example.com");
        User user2 = new User("2", "Jane Smith", "jane@example.com");

        // Create tasks
        Task task1 = new Task("1", "Task 1", "Description 1", new Date(), TaskPriority.LOW, user1);
        Task task2 = new Task("2", "Task 2", "Description 2", new Date(), TaskPriority.MEDIUM, user2);
        Task task3 = new Task("3", "Task 3", "Description 3", new Date(), TaskPriority.HIGH, user1);

        // Add tasks to the task manager
        taskManager.createTask(task1);
        taskManager.createTask(task2);
        taskManager.createTask(task3);

        // Update a task
        task2.setDescription("Updated task2 status");
        taskManager.updateTaskStatus(task2.getId(), TaskStatus.IN_PROGRESS);

        // Search tasks
        List<Task> searchResults = taskManager.searchTasks("Task");
        System.out.println("Tasks with keyword Task:");
        for (Task task : searchResults) {
            System.out.println(task.getTitle());
        }

        // Filter tasks by status
        List<Task> filteredTasks = taskManager.listTasksByStatus(TaskStatus.TODO);
        System.out.println("TODO Tasks:");
        for (Task task : filteredTasks) {
            System.out.println(task.getTitle());
        }

        // Mark a task as done
        taskManager.updateTaskStatus(task2.getId(), TaskStatus.DONE);

        // Get tasks assigned to a user
        List<Task> taskHistory = taskManager.listTasksByUser(user1);
        System.out.println("Task for " + user1.getName() + ":");
        for (Task task : taskHistory) {
            System.out.println(task.getTitle());
        }

        // Delete a task
        taskManager.deleteTask(task3.getId());
    }
}
