import Task from "../Task";
import TaskSortingStrategy from "./TaskSortingStrategy";

export default class SortByPriority implements TaskSortingStrategy {
  private priorityOrder = {
    LOW: 1,
    MEDIUM: 2,
    HIGH: 3,
    CRITICAL: 4,
  };

  sort(tasks: Task[]): void {
    tasks.sort((taskA, taskB) => {
      const priorityA = this.priorityOrder[taskA.getPriority()];
      const priorityB = this.priorityOrder[taskB.getPriority()];

      // Sort in descending order (Critical > High > Medium > Low)
      return priorityB - priorityA;
    });
  }
}
