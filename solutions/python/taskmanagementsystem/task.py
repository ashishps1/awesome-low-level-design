from enum import Enum
from datetime import datetime

class TaskStatus(Enum):
    PENDING = 1
    IN_PROGRESS = 2
    COMPLETED = 3

class Task:
    def __init__(self, task_id, title, description, due_date, priority, assigned_user):
        self.id = task_id
        self.title = title
        self.description = description
        self.due_date = due_date
        self.priority = priority
        self.status = TaskStatus.PENDING
        self.assigned_user = assigned_user

    # Getters and setters
    def get_id(self):
        return self.id

    def get_title(self):
        return self.title

    def get_description(self):
        return self.description

    def get_priority(self):
        return self.priority

    def get_due_date(self):
        return self.due_date

    def get_status(self):
        return self.status

    def get_assigned_user(self):
        return self.assigned_user

    def set_title(self, title):
        self.title = title

    def set_description(self, description):
        self.description = description

    def set_due_date(self, due_date):
        self.due_date = due_date

    def set_priority(self, priority):
        self.priority = priority

    def set_status(self, status):
        self.status = status