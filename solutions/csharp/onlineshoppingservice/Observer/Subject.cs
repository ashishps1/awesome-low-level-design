abstract class Subject
{
    private readonly List<IOrderObserver> observers = new List<IOrderObserver>();

    public void AddObserver(IOrderObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IOrderObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers(Order order)
    {
        foreach (var observer in observers)
        {
            observer.Update(order);
        }
    }
}