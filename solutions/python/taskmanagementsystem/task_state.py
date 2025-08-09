from abc import ABC, abstractmethod
from task_status import TaskStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from task import Task

class TaskState(ABC):
    @abstractmethod
    def start_progress(self, task: 'Task'):
        pass
    
    @abstractmethod
    def complete_task(self, task: 'Task'):
        pass
    
    @abstractmethod
    def reopen_task(self, task: 'Task'):
        pass
    
    @abstractmethod
    def get_status(self) -> TaskStatus:
        pass

class TodoState(TaskState):
    def start_progress(self, task: 'Task'):
        task.set_state(InProgressState())
    
    def complete_task(self, task: 'Task'):
        print("Cannot complete a task that is not in progress.")
    
    def reopen_task(self, task: 'Task'):
        print("Task is already in TO-DO state.")
    
    def get_status(self) -> TaskStatus:
        return TaskStatus.TODO

class InProgressState(TaskState):
    def start_progress(self, task: 'Task'):
        print("Task is already in progress.")
    
    def complete_task(self, task: 'Task'):
        task.set_state(DoneState())
    
    def reopen_task(self, task: 'Task'):
        task.set_state(TodoState())
    
    def get_status(self) -> TaskStatus:
        return TaskStatus.IN_PROGRESS

class DoneState(TaskState):
    def start_progress(self, task: 'Task'):
        print("Cannot start a completed task. Reopen it first.")
    
    def complete_task(self, task: 'Task'):
        print("Task is already done.")
    
    def reopen_task(self, task: 'Task'):
        task.set_state(TodoState())
    
    def get_status(self) -> TaskStatus:
        return TaskStatus.DONE