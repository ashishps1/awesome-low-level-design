import { TaskPriorityEnum } from "./TaskPriorityEnum";
import { TaskStatusEnum } from "./TaskStatusEnum";
import { v4 as uuidv4 } from "uuid";
import User from "./User";
import Comment from "./Comment";
import ActivityLog from "./ActivityLog";

export default class Task {
  private id: string;
  private title: string;
  private description: string;
  private priority: TaskPriorityEnum;
  private status: TaskStatusEnum;
  private dueDate: Date;
  private createdBy: User;
  private assignedTo: User | null;

  private comments: Comment[];
  private subtasks: Task[];
  private history: ActivityLog[];

  constructor(
    title: string,
    description: string,
    dueDate: Date,
    priority: TaskPriorityEnum,
    createdBy: User,
  ) {
    this.id = uuidv4(); // from uuid package
    this.title = title;
    this.description = description;
    this.priority = priority;
    this.dueDate = dueDate;
    this.createdBy = createdBy;

    this.status = TaskStatusEnum.TODO;
    this.assignedTo = null;
    this.comments = [];
    this.subtasks = [];
    this.history = [];
    this.logActivity("Created");
  }

  addComment(comment: Comment) {
    this.comments.push(comment);
    this.logActivity("Comment added by " + comment.getAuthor().getName());
  }

  addSubtask(subtask: Task) {
    this.subtasks.push(subtask);
    this.logActivity("Subtask added: " + subtask.getTitle());
  }

  logActivity(action: string) {
    this.history.push(new ActivityLog(action, this.createdBy));
  }

  updateStatus(status: TaskStatusEnum) {
    this.status = status;
    this.logActivity("Status changed to " + status);
  }

  updatePriority(priority: TaskPriorityEnum) {
    this.priority = priority;
    this.logActivity("Priority changed to " + priority);
  }

  assignUser(user: User) {
    this.assignedTo = user;
    this.logActivity("Assigned to " + user.getName());
  }

  getId() {
    return this.id;
  }

  getTitle() {
    return this.title;
  }

  getPriority() {
    return this.priority;
  }

  getDueDate() {
    return this.dueDate;
  }

  getAssignedTo() {
    return this.assignedTo;
  }

  getCreatedBy() {
    return this.createdBy;
  }

  getDescription() {
    return this.description;
  }

  getStatus() {
    return this.status;
  }
}
