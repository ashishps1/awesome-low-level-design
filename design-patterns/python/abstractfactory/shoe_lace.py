from abc import ABC, abstractmethod


class ShoeLace(ABC):
    """Abstract Product - ShoeLace"""
    
    @abstractmethod
    def get_lace_type(self) -> str:
        pass