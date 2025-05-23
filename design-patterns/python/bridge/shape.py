from abc import ABC, abstractmethod
from .renderer import Renderer


class Shape(ABC):
    """Abstraction - Shape that uses a renderer"""
    
    def __init__(self, renderer: Renderer):
        self._renderer = renderer
    
    @abstractmethod
    def draw(self) -> None:
        pass
    
    @abstractmethod
    def resize(self, factor: float) -> None:
        pass