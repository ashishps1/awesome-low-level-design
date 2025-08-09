from datetime import datetime

class ActivityLog:
    def __init__(self, description: str):
        self._description = description
        self._timestamp = datetime.now()
    
    def __str__(self) -> str:
        return f"[{self._timestamp}] {self._description}"