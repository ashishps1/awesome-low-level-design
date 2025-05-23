using System;

namespace Composite
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create a file system structure
            var root = new Folder("Root");
            
            var documents = new Folder("Documents");
            var downloads = new Folder("Downloads");
            var pictures = new Folder("Pictures");

            var file1 = new File("readme.txt", 1024);
            var file2 = new File("document.pdf", 2048);
            var file3 = new File("image.jpg", 4096);
            var file4 = new File("video.mp4", 8192);

            // Build the structure
            root.Add(documents);
            root.Add(downloads);
            root.Add(pictures);

            documents.Add(file1);
            documents.Add(file2);
            downloads.Add(file3);
            pictures.Add(file4);

            // Print the structure
            Console.WriteLine("=== File System Structure ===");
            root.PrintStructure("");

            // Get total size
            Console.WriteLine($"\nTotal size: {root.GetSize()} bytes");

            // Delete a folder
            Console.WriteLine("\n=== Deleting Documents Folder ===");
            documents.Delete();
        }
    }
} 