from .shape import Shape
from .renderer import Renderer


class Circle(Shape):
    """Refined Abstraction - Circle"""
    
    def __init__(self, renderer: Renderer, radius: float):
        super().__init__(renderer)
        self._radius = radius
    
    def draw(self) -> None:
        self._renderer.render_circle(self._radius)
    
    def resize(self, factor: float) -> None:
        self._radius *= factor
        print(f"Circle resized. New radius: {self._radius}")
    
    @property
    def radius(self) -> float:
        return self._radius