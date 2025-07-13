import Task from "../Task";
import TaskSortingStrategy from "./TaskSortingStrategy";

export default class SortByDueDate implements TaskSortingStrategy {
  sort(tasks: Task[]) {
    tasks.sort((taskA, taskB) => {
      const dueDateA = taskA.getDueDate();
      const dueDateB = taskB.getDueDate();

      // Sort in ascending order (earliest due date first)
      return dueDateA.getTime() - dueDateB.getTime();
    });
  }
}
