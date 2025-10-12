import threading
import uuid

class User:
    def __init__(self, name: str):
        self.id = str(uuid.uuid4())
        self.name = name
        self.reputation = 0
        self._lock = threading.Lock()

    def update_reputation(self, change: int):
        with self._lock:
            self.reputation += change

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_reputation(self) -> int:
        with self._lock:
            return self.reputation