abstract class Subject
{
    private readonly List<IArtistObserver> observers = new List<IArtistObserver>();

    public void AddObserver(IArtistObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IArtistObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers(Artist artist, Album album)
    {
        foreach (var observer in observers)
        {
            observer.Update(artist, album);
        }
    }
}