using System;

namespace Bridge
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create renderers
            var vectorRenderer = new VectorRenderer();
            var rasterRenderer = new RasterRenderer();

            // Create shapes with vector renderer
            Console.WriteLine("=== Drawing with Vector Renderer ===");
            var vectorCircle = new Circle(vectorRenderer, 5);
            var vectorRectangle = new Rectangle(vectorRenderer, 10, 5);

            vectorCircle.Draw();
            vectorRectangle.Draw();

            // Create shapes with raster renderer
            Console.WriteLine("\n=== Drawing with Raster Renderer ===");
            var rasterCircle = new Circle(rasterRenderer, 5);
            var rasterRectangle = new Rectangle(rasterRenderer, 10, 5);

            rasterCircle.Draw();
            rasterRectangle.Draw();
        }
    }
} 