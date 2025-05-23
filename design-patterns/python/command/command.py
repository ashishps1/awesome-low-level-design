from abc import ABC, abstractmethod


class Command(ABC):
    """Command interface"""
    
    @abstractmethod
    def execute(self) -> None:
        pass
    
    @abstractmethod
    def undo(self) -> None:
        pass