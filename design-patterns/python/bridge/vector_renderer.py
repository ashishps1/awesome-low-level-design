from .renderer import Renderer


class VectorRenderer(Renderer):
    """Concrete Implementation for vector rendering"""
    
    def render_circle(self, radius: float) -> None:
        print(f"VectorRenderer: Drawing circle with radius {radius}")
    
    def render_rectangle(self, width: float, height: float) -> None:
        print(f"VectorRenderer: Drawing rectangle {width}x{height}")