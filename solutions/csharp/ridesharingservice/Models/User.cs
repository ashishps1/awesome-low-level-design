abstract class User : ITripObserver
{
    private readonly string id;
    private readonly string name;
    private readonly string contact;
    private readonly List<Trip> tripHistory;

    private static int idCounter = 0;

    public User(string n, string c)
    {
        id = $"user_{++idCounter}";
        name = n;
        contact = c;
        tripHistory = new List<Trip>();
    }

    public void AddTripToHistory(Trip trip)
    {
        tripHistory.Add(trip);
    }

    public List<Trip> TripHistory => tripHistory;
    public string Id => id;
    public string Name => name;
    public string Contact => contact;

    public abstract void OnUpdate(Trip trip);
}