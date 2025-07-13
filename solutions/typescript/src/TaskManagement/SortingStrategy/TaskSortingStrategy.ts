import Task from "../Task";

export default interface TaskSortingStrategy {
  sort(tasks: Task[]): void;
}
