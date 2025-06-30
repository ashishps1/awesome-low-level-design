package taskmanagementsystem;

import taskmanagementsystem.sortingstrategy.SortByDueDate;

import java.util.Date;
import java.util.List;

public class TaskManagementSystemDemo {
    public static void run() {
        TaskManagementSystem taskManagementSystem = TaskManagementSystem.getInstance();

        // Create users
        User user1 = taskManagementSystem.createUser("John Doe", "john@example.com");
        User user2 = taskManagementSystem.createUser("Jane Smith", "jane@example.com");

        // Create task lists
        TaskList taskList1 = taskManagementSystem.createTaskList("Enhancements");
        TaskList taskList2 = taskManagementSystem.createTaskList("Bug Fix");

        // Create tasks
        Task task1 = taskManagementSystem.createTask(taskList1.getId(), "Task 1", "Description 1",
                new Date(), TaskPriority.LOW, user1.getId());
        Task task2 = taskManagementSystem.createTask(taskList1.getId(), "Task 2", "Description 2",
                new Date(), TaskPriority.MEDIUM, user1.getId());
        Task task3 = taskManagementSystem.createTask(taskList2.getId(), "Task 3", "Description 3",
                new Date(), TaskPriority.HIGH, user2.getId());

        // Update task status
        taskManagementSystem.updateTaskStatus(task2.getId(), TaskStatus.IN_PROGRESS);

        // Assign task
        taskManagementSystem.assignTask(task2.getId(), user2.getId());

        // Search tasks
        List<Task> searchResults = taskManagementSystem.searchTasks("Task", new SortByDueDate());
        System.out.println("\nTasks with keyword Task:");
        for (Task task : searchResults) {
            System.out.println(task.getTitle());
        }

        // Filter tasks by status
        List<Task> filteredTasks = taskManagementSystem.listTasksByStatus(TaskStatus.TODO);
        System.out.println("\nTODO Tasks:");
        for (Task task : filteredTasks) {
            System.out.println(task.getTitle());
        }

        // Mark a task as done
        taskManagementSystem.updateTaskStatus(task2.getId(), TaskStatus.DONE);

        // Get tasks assigned to a user
        List<Task> userTaskList = taskManagementSystem.listTasksByUser(user2.getId());
        System.out.println("\nTask for " + user2.getName() + ":");
        for (Task task : userTaskList) {
            System.out.println(task.getTitle());
        }

        // Delete a task
        taskManagementSystem.deleteTask(task3.getId());
    }
}
