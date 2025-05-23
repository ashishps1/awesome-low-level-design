from abc import ABC, abstractmethod


class Sole(ABC):
    """Abstract Product - Sole"""
    
    @abstractmethod
    def get_sole_type(self) -> str:
        pass