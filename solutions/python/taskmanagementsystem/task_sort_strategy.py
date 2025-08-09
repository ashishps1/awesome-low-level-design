from abc import ABC, abstractmethod
from typing import List
from task import Task
from task_priority import TaskPriority
from datetime import date

class TaskSortStrategy(ABC):
    @abstractmethod
    def sort(self, tasks: List[Task]):
        pass

class SortByPriority(TaskSortStrategy):
    def sort(self, tasks: List[Task]):
        # Higher priority comes first (CRITICAL > HIGH > MEDIUM > LOW)
        priority_order = {TaskPriority.CRITICAL: 4, TaskPriority.HIGH: 3, 
                         TaskPriority.MEDIUM: 2, TaskPriority.LOW: 1}
        tasks.sort(key=lambda task: priority_order.get(task.get_priority(), 0), reverse=True)

class SortByDueDate(TaskSortStrategy):
    def sort(self, tasks: List[Task]):
        tasks.sort(key=lambda task: task.get_due_date() if task.get_due_date() else date.max)