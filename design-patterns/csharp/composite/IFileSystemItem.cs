namespace Composite
{
    public interface IFileSystemItem
    {
        int GetSize();
        void PrintStructure(string indent);
        void Delete();
    }
} 