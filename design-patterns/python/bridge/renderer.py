from abc import ABC, abstractmethod


class Renderer(ABC):
    """Implementation interface for rendering shapes"""
    
    @abstractmethod
    def render_circle(self, radius: float) -> None:
        pass
    
    @abstractmethod
    def render_rectangle(self, width: float, height: float) -> None:
        pass