from .circle import Circle
from .rectangle import Rectangle
from .vector_renderer import VectorRenderer
from .raster_renderer import RasterRenderer


def bridge_demo():
    """Demonstrate Bridge pattern"""
    print("=== Bridge Pattern Demo ===")
    
    # Create renderers
    vector_renderer = VectorRenderer()
    raster_renderer = RasterRenderer()
    
    # Create shapes with different renderers
    print("\n--- Vector Rendering ---")
    vector_circle = Circle(vector_renderer, 5.0)
    vector_rectangle = Rectangle(vector_renderer, 10.0, 8.0)
    
    vector_circle.draw()
    vector_rectangle.draw()
    
    print("\n--- Raster Rendering ---")
    raster_circle = Circle(raster_renderer, 3.0)
    raster_rectangle = Rectangle(raster_renderer, 6.0, 4.0)
    
    raster_circle.draw()
    raster_rectangle.draw()
    
    # Demonstrate resizing
    print("\n--- Resizing Shapes ---")
    vector_circle.resize(2.0)
    vector_circle.draw()
    
    raster_rectangle.resize(1.5)
    raster_rectangle.draw()
    
    print("\n--- Mixed Combinations ---")
    # Show that shapes and renderers can be combined freely
    shapes = [
        Circle(vector_renderer, 2.0),
        Circle(raster_renderer, 2.0),
        Rectangle(vector_renderer, 4.0, 3.0),
        Rectangle(raster_renderer, 4.0, 3.0)
    ]
    
    for i, shape in enumerate(shapes, 1):
        print(f"Shape {i}: ", end="")
        shape.draw()


if __name__ == "__main__":
    bridge_demo()