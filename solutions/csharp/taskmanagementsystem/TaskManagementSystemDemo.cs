using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class TaskManagementSystemDemo
{
    public static void Main()
    {
        TaskManagementSystem taskManagementSystem = TaskManagementSystem.GetInstance();

        // Create users
        User user1 = taskManagementSystem.CreateUser("John Doe", "john@example.com");
        User user2 = taskManagementSystem.CreateUser("Jane Smith", "jane@example.com");

        // Create task lists
        TaskList taskList1 = taskManagementSystem.CreateTaskList("Enhancements");
        TaskList taskList2 = taskManagementSystem.CreateTaskList("Bug Fix");

        // Create tasks
        Task task1 = taskManagementSystem.CreateTask("Enhancement Task", "Launch New Feature",
                "2024-02-15", TaskPriority.LOW, user1.GetId());
        Task subtask1 = taskManagementSystem.CreateTask("Enhancement sub task", "Design UI/UX",
                "2024-02-14", TaskPriority.MEDIUM, user1.GetId());
        Task task2 = taskManagementSystem.CreateTask("Bug Fix Task", "Fix API Bug",
                "2024-02-16", TaskPriority.HIGH, user2.GetId());

        task1.AddSubtask(subtask1);

        taskList1.AddTask(task1);
        taskList2.AddTask(task2);

        taskList1.Display();

        // Update task status
        subtask1.StartProgress();

        // Assign task
        subtask1.SetAssignee(user2);

        taskList1.Display();

        // Search tasks
        List<Task> searchResults = taskManagementSystem.SearchTasks("Task", new SortByDueDate());
        Console.WriteLine("\nTasks with keyword Task:");
        foreach (Task task in searchResults)
        {
            Console.WriteLine(task.GetTitle());
        }

        // Filter tasks by status
        List<Task> filteredTasks = taskManagementSystem.ListTasksByStatus(TaskStatus.TODO);
        Console.WriteLine("\nTODO Tasks:");
        foreach (Task task in filteredTasks)
        {
            Console.WriteLine(task.GetTitle());
        }

        // Mark a task as done
        subtask1.CompleteTask();

        // Get tasks assigned to a user
        List<Task> userTaskList = taskManagementSystem.ListTasksByUser(user2.GetId());
        Console.WriteLine($"\nTask for {user2.GetName()}:");
        foreach (Task task in userTaskList)
        {
            Console.WriteLine(task.GetTitle());
        }

        taskList1.Display();

        // Delete a task
        taskManagementSystem.DeleteTask(task2.GetId());
    }
}