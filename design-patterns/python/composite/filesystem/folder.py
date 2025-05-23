from typing import List
from .file_system_item import FileSystemItem

class Folder(FileSystemItem):
    def __init__(self, name: str):
        self.name = name
        self.items: List[FileSystemItem] = []

    def add_item(self, item: FileSystemItem) -> None:
        self.items.append(item)

    def remove_item(self, item: FileSystemItem) -> None:
        self.items.remove(item)

    def get_size(self) -> int:
        total_size = 0
        for item in self.items:
            total_size += item.get_size()
        return total_size

    def __str__(self) -> str:
        return f"Folder: {self.name} ({self.get_size()} bytes)" 