using System;
using System.Collections.Generic;

namespace Composite
{
    public class Folder : IFileSystemItem
    {
        private readonly string name;
        private readonly List<IFileSystemItem> children;

        public Folder(string name)
        {
            this.name = name;
            this.children = new List<IFileSystemItem>();
        }

        public void Add(IFileSystemItem item)
        {
            children.Add(item);
        }

        public void Remove(IFileSystemItem item)
        {
            children.Remove(item);
        }

        public int GetSize()
        {
            int totalSize = 0;
            foreach (var child in children)
            {
                totalSize += child.GetSize();
            }
            return totalSize;
        }

        public void PrintStructure(string indent)
        {
            Console.WriteLine($"{indent}Folder: {name}");
            foreach (var child in children)
            {
                child.PrintStructure(indent + "  ");
            }
        }

        public void Delete()
        {
            Console.WriteLine($"Deleting folder: {name}");
            foreach (var child in children)
            {
                child.Delete();
            }
        }
    }
} 