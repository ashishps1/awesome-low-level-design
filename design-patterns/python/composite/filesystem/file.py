from typing import List
from .file_system_item import FileSystemItem

class File(FileSystemItem):
    def __init__(self, name: str, size: int):
        self.name = name
        self.size = size

    def get_size(self) -> int:
        return self.size

    def __str__(self) -> str:
        return f"File: {self.name} ({self.size} bytes)" 