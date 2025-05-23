using System;

namespace Composite
{
    public class File : IFileSystemItem
    {
        private readonly string name;
        private readonly int size;

        public File(string name, int size)
        {
            this.name = name;
            this.size = size;
        }

        public int GetSize()
        {
            return size;
        }

        public void PrintStructure(string indent)
        {
            Console.WriteLine($"{indent}File: {name} ({size} bytes)");
        }

        public void Delete()
        {
            Console.WriteLine($"Deleting file: {name}");
        }
    }
} 