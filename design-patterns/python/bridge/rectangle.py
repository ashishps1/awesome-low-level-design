from .shape import Shape
from .renderer import Renderer


class Rectangle(Shape):
    """Refined Abstraction - Rectangle"""
    
    def __init__(self, renderer: Renderer, width: float, height: float):
        super().__init__(renderer)
        self._width = width
        self._height = height
    
    def draw(self) -> None:
        self._renderer.render_rectangle(self._width, self._height)
    
    def resize(self, factor: float) -> None:
        self._width *= factor
        self._height *= factor
        print(f"Rectangle resized. New dimensions: {self._width}x{self._height}")
    
    @property
    def width(self) -> float:
        return self._width
    
    @property
    def height(self) -> float:
        return self._height