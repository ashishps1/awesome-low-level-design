import Task from "./Task";
import { TaskPriorityEnum } from "./TaskPriorityEnum";
import { TaskStatusEnum } from "./TaskStatusEnum";
import User from "./User";
import TaskList from "./TaskList";
import Comment from "./Comment";
import TaskSortingStrategy from "./SortingStrategy/TaskSortingStrategy";

export default class TaskManagementSystem {
  private static instance: TaskManagementSystem | null;
  private users: Map<String, User>;
  private tasks: Map<String, Task>;
  private taskLists: Map<String, TaskList>;

  private constructor() {
    this.users = new Map();
    this.tasks = new Map();
    this.taskLists = new Map();
  }

  static getInstance() {
    if (!TaskManagementSystem.instance) {
      TaskManagementSystem.instance = new TaskManagementSystem();
    }
    return TaskManagementSystem.instance;
  }

  createUser(name: string, email: string) {
    const user = new User(name, email);
    this.users.set(user.getId(), user);
    return user;
  }

  createTaskList(listName: string) {
    const taskList = new TaskList(listName);
    this.taskLists.set(taskList.getId(), taskList);
    return taskList;
  }

  createTask(
    listId: string,
    title: string,
    description: string,
    dueDate: Date,
    priority: TaskPriorityEnum,
    createdByUserId: string,
  ) {
    const taskList = this.taskLists.get(listId);
    if (taskList == null) throw new Error("TaskList not found.");

    const createdBy = this.users.get(createdByUserId);
    if (createdBy == null) throw new Error("User not found.");

    const task = new Task(title, description, dueDate, priority, createdBy);

    this.tasks.set(task.getId(), task);
    taskList.addTask(task);
    return task;
  }

  getTaskById(taskId: string) {
    const task = this.tasks.get(taskId);
    if (!task) {
      throw new Error("Task not found: " + taskId);
    }
    return task;
  }

  updateTaskStatus(taskId: string, status: TaskStatusEnum) {
    this.getTaskById(taskId).updateStatus(status);
  }

  updateTaskPriority(taskId: string, priority: TaskPriorityEnum) {
    this.getTaskById(taskId).updatePriority(priority);
  }

  assignTask(taskId: string, userId: string) {
    const user = this.users.get(userId);
    if (user == null) throw new Error("User not found.");
    this.getTaskById(taskId).assignUser(user);
  }

  addComment(taskId: string, commentText: string, author: User) {
    const task = this.getTaskById(taskId);
    task.addComment(new Comment(commentText, author));
  }

  listTasksByUser(userId: string) {
    return [...this.tasks.values()].filter(
      (task) => userId == task.getAssignedTo()?.getId(),
    );
  }

  listTasksByStatus(status: TaskStatusEnum) {
    return [...this.tasks.values()].filter(
      (task) => task.getStatus() == status,
    );
  }

  deleteTask(taskId: string) {
    this.tasks.delete(taskId);
  }

  searchTasks(keyword: string, sortingStrategy: TaskSortingStrategy) {
    const matchingTasks = [];
    for (const task of this.tasks.values()) {
      if (
        task.getTitle().includes(keyword) ||
        task.getDescription().includes(keyword)
      ) {
        matchingTasks.push(task);
      }
    }
    sortingStrategy.sort(matchingTasks);
    return matchingTasks;
  }
}
