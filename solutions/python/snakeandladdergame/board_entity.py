from abc import ABC

class BoardEntity(ABC):
    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end
    
    def get_start(self) -> int:
        return self.start
    
    def get_end(self) -> int:
        return self.end