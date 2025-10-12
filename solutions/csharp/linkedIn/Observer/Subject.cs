abstract class Subject
{
    private readonly List<INotificationObserver> observers = new List<INotificationObserver>();

    public void AddObserver(INotificationObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(INotificationObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers(Notification notification)
    {
        foreach (var observer in observers)
        {
            observer.Update(notification);
        }
    }
}