from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from task import Task

class TaskObserver(ABC):
    @abstractmethod
    def update(self, task: 'Task', change_type: str):
        pass

class ActivityLogger(TaskObserver):
    def update(self, task: 'Task', change_type: str):
        print(f"LOGGER: Task '{task.get_title()}' was updated. Change: {change_type}")