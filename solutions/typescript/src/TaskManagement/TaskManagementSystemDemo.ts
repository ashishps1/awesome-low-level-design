import SortByDueDate from "./SortingStrategy/SortByDueDate";
import TaskManagementSystem from "./TaskManagementSystem";
import { TaskPriorityEnum } from "./TaskPriorityEnum";
import { TaskStatusEnum } from "./TaskStatusEnum";

export default class TaskManagementDemo {
  static run() {
    const taskManagementSystem = TaskManagementSystem.getInstance();

    // Create users
    const user1 = taskManagementSystem.createUser(
      "John Doe",
      "john@example.com",
    );
    const user2 = taskManagementSystem.createUser(
      "Jane Smith",
      "jane@example.com",
    );

    // Create task lists
    const taskList1 = taskManagementSystem.createTaskList("Enhancements");
    const taskList2 = taskManagementSystem.createTaskList("Bug Fix");

    // Create tasks
    const task1 = taskManagementSystem.createTask(
      taskList1.getId(),
      "Task 1",
      "Description 1",
      new Date(),
      TaskPriorityEnum.LOW,
      user1.getId(),
    );
    const task2 = taskManagementSystem.createTask(
      taskList1.getId(),
      "Task 2",
      "Description 2",
      new Date(),
      TaskPriorityEnum.MEDIUM,
      user1.getId(),
    );
    const task3 = taskManagementSystem.createTask(
      taskList2.getId(),
      "Task 3",
      "Description 3",
      new Date(),
      TaskPriorityEnum.HIGH,
      user2.getId(),
    );

    // Update task status
    taskManagementSystem.updateTaskStatus(
      task2.getId(),
      TaskStatusEnum.IN_PROGRESS,
    );

    // Assign task
    taskManagementSystem.assignTask(task2.getId(), user2.getId());

    // Search tasks
    const searchResults = taskManagementSystem.searchTasks(
      "Task",
      new SortByDueDate(),
    );
    console.log("\nTasks with keyword Task:");
    for (const task of searchResults) {
      console.log(task.getTitle());
    }

    // Filter tasks by status
    const filteredTasks = taskManagementSystem.listTasksByStatus(
      TaskStatusEnum.TODO,
    );
    console.log("\nTODO Tasks:");
    for (const task of filteredTasks) {
      console.log(task.getTitle());
    }

    // Mark a task as done
    taskManagementSystem.updateTaskStatus(task2.getId(), TaskStatusEnum.DONE);

    // Get tasks assigned to a user
    const userTaskList = taskManagementSystem.listTasksByUser(user2.getId());
    console.log("\nTask for " + user2.getName() + ":");
    for (const task of userTaskList) {
      console.log(task.getTitle());
    }

    // Delete a task
    taskManagementSystem.deleteTask(task3.getId());
  }
}
