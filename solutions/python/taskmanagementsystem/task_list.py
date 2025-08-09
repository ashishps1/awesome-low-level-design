import threading
import uuid
from typing import List
from task import Task

class TaskList:
    def __init__(self, name: str):
        self._id = str(uuid.uuid4())
        self._name = name
        self._tasks: List[Task] = []
        self._lock = threading.Lock()
    
    def add_task(self, task: Task):
        with self._lock:
            self._tasks.append(task)
    
    def get_tasks(self) -> List[Task]:
        with self._lock:
            return self._tasks.copy()  # Return a copy to prevent external modification
    
    @property
    def id(self) -> str:
        return self._id
    
    @property
    def name(self) -> str:
        return self._name
    
    def display(self):
        print(f"--- Task List: {self._name} ---")
        for task in self._tasks:
            task.display("")
        print("-----------------------------------")