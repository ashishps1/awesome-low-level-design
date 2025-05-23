using System;

namespace Proxy
{
    public class ImageProxy : IImage
    {
        private string fileName;
        private HighResolutionImage realImage; // RealSubject

        public ImageProxy(string fileName)
        {
            this.fileName = fileName;
            Console.WriteLine($"ImageProxy: Created for {fileName}. Real image not loaded yet.");
        }

        public string GetFileName()
        {
            // Can safely return without loading the image
            return fileName;
        }

        public void Display()
        {
            // Lazy initialization: Load only when Display() is called
            if (realImage == null)
            {
                Console.WriteLine($"ImageProxy: Display() requested for {fileName}. Loading high-resolution image...");
                realImage = new HighResolutionImage(fileName);
            }
            else
            {
                Console.WriteLine($"ImageProxy: Using cached high-resolution image for {fileName}");
            }

            // Delegate the display call to the real image
            realImage.Display();
        }
    }
} 