using System;

namespace Proxy
{
    class ImageGalleryApp
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Application Started. Initializing image proxies for gallery...");

            // Create lightweight proxies instead of full image objects
            IImage image1 = new ImageProxy("photo1.jpg");
            IImage image2 = new ImageProxy("photo2.png"); // Never displayed
            IImage image3 = new ImageProxy("photo3.gif");

            Console.WriteLine("\nGallery initialized. No images actually loaded yet.");
            Console.WriteLine($"Image 1 Filename: {image1.GetFileName()}"); // Does not trigger image load

            // User clicks on image1
            Console.WriteLine($"\nUser requests to display {image1.GetFileName()}");
            image1.Display(); // Lazy loading happens here

            // User clicks on image1 again
            Console.WriteLine($"\nUser requests to display {image1.GetFileName()} again.");
            image1.Display(); // Already loaded; no loading delay

            // User clicks on image3
            Console.WriteLine($"\nUser requests to display {image3.GetFileName()}");
            image3.Display(); // Triggers loading for image3

            Console.WriteLine("\nApplication finished. Note: photo2.png was never loaded.");
        }
    }
} 