from abc import ABC, abstractmethod


class TextView(ABC):
    """Component interface for text display"""
    
    @abstractmethod
    def show(self) -> str:
        pass