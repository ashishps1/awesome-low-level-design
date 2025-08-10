abstract class MovieSubject
{
    private readonly List<IMovieObserver> observers = new List<IMovieObserver>();

    public void AddObserver(IMovieObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IMovieObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.Update((Movie)this);
        }
    }
}