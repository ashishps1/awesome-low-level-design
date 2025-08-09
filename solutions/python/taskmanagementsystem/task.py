import threading
from typing import List, Optional, Set
from datetime import date
import uuid
from user import User
from task_priority import TaskPriority
from task_status import TaskStatus
from comment import Comment
from activity_log import ActivityLog
from task_state import TodoState, TaskState
from task_observer import TaskObserver
from tag import Tag

class Task:
    def __init__(self, builder: 'TaskBuilder'):
        self._id = builder._id
        self._title = builder._title
        self._description = builder._description
        self._due_date = builder._due_date
        self._priority = builder._priority
        self._created_by = builder._created_by
        self._assignee = builder._assignee
        self._tags = builder._tags
        self._current_state = TodoState()  # Initial state
        self._comments: List[Comment] = []
        self._subtasks: List['Task'] = []
        self._activity_logs: List[ActivityLog] = []
        self._observers: List[TaskObserver] = []
        self._lock = threading.Lock()
        self.add_log(f"Task created with title: {self._title}")
    
    def set_assignee(self, user: User):
        with self._lock:
            self._assignee = user
            self.add_log(f"Assigned to {user.name}")
            self.notify_observers("assignee")
    
    def update_priority(self, priority: TaskPriority):
        with self._lock:
            self._priority = priority
            self.notify_observers("priority")
    
    def add_comment(self, comment: Comment):
        with self._lock:
            self._comments.append(comment)
            self.add_log(f"Comment added by {comment.author.name}")
            self.notify_observers("comment")
    
    def add_subtask(self, subtask: 'Task'):
        with self._lock:
            self._subtasks.append(subtask)
            self.add_log(f"Subtask added: {subtask.get_title()}")
            self.notify_observers("subtask_added")
    
    # State Pattern Methods
    def set_state(self, state: TaskState):
        self._current_state = state
        self.add_log(f"Status changed to: {state.get_status().value}")
        self.notify_observers("status")
    
    def start_progress(self):
        self._current_state.start_progress(self)
    
    def complete_task(self):
        self._current_state.complete_task(self)
    
    def reopen_task(self):
        self._current_state.reopen_task(self)
    
    # Observer Pattern Methods
    def add_observer(self, observer: TaskObserver):
        self._observers.append(observer)
    
    def remove_observer(self, observer: TaskObserver):
        if observer in self._observers:
            self._observers.remove(observer)
    
    def notify_observers(self, change_type: str):
        for observer in self._observers:
            observer.update(self, change_type)
    
    def add_log(self, log_description: str):
        self._activity_logs.append(ActivityLog(log_description))
    
    def is_composite(self) -> bool:
        return len(self._subtasks) > 0
    
    def display(self, indent: str = ""):
        print(f"{indent}- {self._title} [{self.get_status().value}, {self._priority.value}, Due: {self._due_date}]")
        if self.is_composite():
            for subtask in self._subtasks:
                subtask.display(indent + "  ")
    
    # Getters and setters
    def get_id(self) -> str:
        return self._id
    
    def get_title(self) -> str:
        return self._title
    
    def get_description(self) -> str:
        return self._description
    
    def get_priority(self) -> TaskPriority:
        return self._priority
    
    def get_due_date(self) -> date:
        return self._due_date
    
    def get_assignee(self) -> Optional[User]:
        return self._assignee
    
    def set_title(self, title: str):
        self._title = title
    
    def set_description(self, description: str):
        self._description = description
    
    def get_status(self) -> TaskStatus:
        return self._current_state.get_status()
    
    # Builder Pattern
    class TaskBuilder:
        def __init__(self, title: str):
            self._id = str(uuid.uuid4())
            self._title = title
            self._description = ""
            self._due_date = None
            self._priority = None
            self._created_by = None
            self._assignee = None
            self._tags = set()
        
        def description(self, description: str) -> 'Task.TaskBuilder':
            self._description = description
            return self
        
        def due_date(self, due_date: date) -> 'Task.TaskBuilder':
            self._due_date = due_date
            return self
        
        def priority(self, priority: TaskPriority) -> 'Task.TaskBuilder':
            self._priority = priority
            return self
        
        def assignee(self, assignee: User) -> 'Task.TaskBuilder':
            self._assignee = assignee
            return self
        
        def created_by(self, created_by: User) -> 'Task.TaskBuilder':
            self._created_by = created_by
            return self
        
        def tags(self, tags: Set[Tag]) -> 'Task.TaskBuilder':
            self._tags = tags
            return self
        
        def build(self) -> 'Task':
            return Task(self)