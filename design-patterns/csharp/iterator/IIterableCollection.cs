namespace Iterator
{
    public interface IIterableCollection<T>
    {
        IIterator<T> CreateIterator();
    }
} 