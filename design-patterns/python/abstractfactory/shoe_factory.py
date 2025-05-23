from abc import ABC, abstractmethod
from .sole import Sole
from .shoe_lace import ShoeLace


class ShoeFactory(ABC):
    """Abstract Factory for creating shoe components"""
    
    @abstractmethod
    def create_shoe_lace(self) -> ShoeLace:
        pass
    
    @abstractmethod
    def create_sole(self) -> Sole:
        pass