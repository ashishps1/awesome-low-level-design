from .renderer import Renderer


class RasterRenderer(Renderer):
    """Concrete Implementation for raster rendering"""
    
    def render_circle(self, radius: float) -> None:
        print(f"RasterRenderer: Painting circle with radius {radius}")
    
    def render_rectangle(self, width: float, height: float) -> None:
        print(f"RasterRenderer: Painting rectangle {width}x{height}")