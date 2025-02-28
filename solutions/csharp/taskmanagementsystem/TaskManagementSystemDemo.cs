using System;
using System.Collections.Generic;

namespace TaskManagementSystem
{
    public class TaskManagementSystemDemo
    {
        public static void Run()
        {
            TaskManager taskManager = TaskManager.GetInstance();

            // Create users
            User user1 = new User("1", "John Doe", "john@example.com");
            User user2 = new User("2", "Jane Smith", "jane@example.com");

            // Create tasks
            Task task1 = new Task("1", "Task 1", "Description 1", DateTime.Now, 1, user1);
            Task task2 = new Task("2", "Task 2", "Description 2", DateTime.Now, 2, user2);
            Task task3 = new Task("3", "Task 3", "Description 3", DateTime.Now, 1, user1);

            // Add tasks to the task manager
            taskManager.CreateTask(task1);
            taskManager.CreateTask(task2);
            taskManager.CreateTask(task3);

            // Update a task
            task2.Description = "Updated description";
            taskManager.UpdateTask(task2);

            // Search tasks
            List<Task> searchResults = taskManager.SearchTasks("Task");
            Console.WriteLine("Search Results:");
            foreach (Task task in searchResults)
            {
                Console.WriteLine(task.Title);
            }

            // Filter tasks
            List<Task> filteredTasks = taskManager.FilterTasks(TaskStatus.PENDING, DateTime.MinValue, DateTime.Now, 1);
            Console.WriteLine("Filtered Tasks:");
            foreach (Task task in filteredTasks)
            {
                Console.WriteLine(task.Title);
            }

            // Mark a task as completed
            taskManager.MarkTaskAsCompleted("1");

            // Get task history for a user
            List<Task> taskHistory = taskManager.GetTaskHistory(user1);
            Console.WriteLine("Task History for " + user1.Name + ":");
            foreach (Task task in taskHistory)
            {
                Console.WriteLine(task.Title);
            }

            // Delete a task
            taskManager.DeleteTask("3");
        }
    }
}