using System;

namespace Bridge
{
    public class RasterRenderer : IRenderer
    {
        public void RenderCircle(float radius)
        {
            Console.WriteLine($"Drawing a circle of radius {radius} using raster graphics");
        }

        public void RenderRectangle(float width, float height)
        {
            Console.WriteLine($"Drawing a rectangle of width {width} and height {height} using raster graphics");
        }
    }
} 