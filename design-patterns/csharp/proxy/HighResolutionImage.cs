using System;
using System.Threading;

namespace Proxy
{
    public class HighResolutionImage : IImage
    {
        private string fileName;
        private byte[] imageData; // Simulate large data

        public HighResolutionImage(string fileName)
        {
            this.fileName = fileName;
            LoadImageFromDisk(); // Expensive operation!
        }

        private void LoadImageFromDisk()
        {
            Console.WriteLine($"Loading image: {fileName} from disk (Expensive Operation)...");
            // Simulate disk read and memory allocation
            Thread.Sleep(2000); // Simulate delay
            this.imageData = new byte[10 * 1024 * 1024]; // 10MB
            Console.WriteLine($"Image {fileName} loaded successfully.");
        }

        public void Display()
        {
            Console.WriteLine($"Displaying image: {fileName}");
            // Actual rendering logic would go here
        }

        public string GetFileName()
        {
            return fileName;
        }
    }
} 