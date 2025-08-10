abstract class GameSubject
{
    private readonly List<IGameObserver> observers = new List<IGameObserver>();

    public void AddObserver(IGameObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IGameObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.Update((Game)this);
        }
    }
}