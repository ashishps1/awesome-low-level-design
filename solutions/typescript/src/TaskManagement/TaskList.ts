import Task from "./Task";
import { v4 as uuidv4 } from "uuid";

export default class TaskList {
  private id: string;
  private name: string;
  private tasks: Task[];

  constructor(name: string) {
    this.id = uuidv4();
    this.name = name;
    this.tasks = [];
  }

  addTask(task: Task) {
    this.tasks.push(task);
  }

  getTasks() {
    return this.tasks;
  }

  getId() {
    return this.id;
  }

  getName() {
    return this.name;
  }
}
