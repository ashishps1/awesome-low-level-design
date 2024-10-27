package taskmanagementsystem

import (
	"fmt"
	"time"
)

func Run() {
	taskManager := GetTaskManager()

	// Create users
	user1 := NewUser("1", "John Doe", "john@example.com")
	user2 := NewUser("2", "Jane Smith", "jane@example.com")

	// Create tasks
	task1 := NewTask("1", "Task 1", "Description 1", time.Now(), 1, user1)
	task2 := NewTask("2", "Task 2", "Description 2", time.Now(), 2, user2)
	task3 := NewTask("3", "Task 3", "Description 3", time.Now(), 1, user1)

	// Add tasks to the task manager
	taskManager.CreateTask(task1)
	taskManager.CreateTask(task2)
	taskManager.CreateTask(task3)

	// Update a task
	task2.SetDescription("Updated description")
	taskManager.UpdateTask(task2)

	// Search tasks
	searchResults := taskManager.SearchTasks("Task")
	fmt.Println("Search Results:")
	for _, task := range searchResults {
		fmt.Println(task.GetTitle())
	}

	// Filter tasks
	filteredTasks := taskManager.FilterTasks(Pending, time.Unix(0, 0), time.Now(), 1)
	fmt.Println("Filtered Tasks:")
	for _, task := range filteredTasks {
		fmt.Println(task.GetTitle())
	}

	// Mark a task as completed
	taskManager.MarkTaskAsCompleted("1")

	// Get task history for a user
	taskHistory := taskManager.GetTaskHistory(user1)
	fmt.Printf("Task History for %s:\n", user1.GetName())
	for _, task := range taskHistory {
		fmt.Println(task.GetTitle())
	}

	// Delete a task
	taskManager.DeleteTask("3")
}
