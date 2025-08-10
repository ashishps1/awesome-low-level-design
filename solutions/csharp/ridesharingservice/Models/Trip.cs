class Trip
{
    private readonly string id;
    private readonly Rider rider;
    private Driver driver;
    private readonly Location pickupLocation;
    private readonly Location dropoffLocation;
    private readonly double fare;
    private TripStatus status;
    private ITripState currentState;
    private readonly List<ITripObserver> observers = new List<ITripObserver>();

    public static int idCounter = 0;

    public Trip(TripBuilder builder)
    {
        id = builder.Id;
        rider = builder.Rider;
        driver = null;
        pickupLocation = builder.PickupLocation;
        dropoffLocation = builder.DropoffLocation;
        fare = builder.Fare;
        status = TripStatus.REQUESTED;
        currentState = new RequestedState();
    }

    public void AddObserver(ITripObserver observer)
    {
        observers.Add(observer);
    }

    private void NotifyObservers()
    {
        foreach (var obs in observers)
        {
            obs.OnUpdate(this);
        }
    }

    public void AssignDriver(Driver d)
    {
        currentState.Assign(this, d);
        AddObserver(d);
        NotifyObservers();
    }

    public void StartTrip()
    {
        currentState.Start(this);
        NotifyObservers();
    }

    public void EndTrip()
    {
        currentState.End(this);
        NotifyObservers();
    }

    // Getters
    public string Id => id;
    public Rider Rider => rider;
    public Driver Driver => driver;
    public Location PickupLocation => pickupLocation;
    public Location DropoffLocation => dropoffLocation;
    public double Fare => fare;
    public TripStatus Status => status;

    // Setters (internal, only to be called by State objects)
    public void SetState(ITripState state)
    {
        currentState = state;
    }

    public void SetStatus(TripStatus s)
    {
        status = s;
    }

    public void SetDriver(Driver d)
    {
        driver = d;
    }

    public override string ToString()
    {
        return $"Trip [id={id}, status={status}, fare=${fare:F2}]";
    }
}

class TripBuilder
{
    private readonly string id;
    private Rider rider;
    private Location pickupLocation;
    private Location dropoffLocation;
    private double fare;

    public TripBuilder()
    {
        id = $"trip_{++Trip.idCounter}";
    }

    public TripBuilder WithRider(Rider r)
    {
        rider = r;
        return this;
    }

    public TripBuilder WithPickupLocation(Location loc)
    {
        pickupLocation = loc;
        return this;
    }

    public TripBuilder WithDropoffLocation(Location loc)
    {
        dropoffLocation = loc;
        return this;
    }

    public TripBuilder WithFare(double f)
    {
        fare = f;
        return this;
    }

    public Trip Build()
    {
        if (rider == null || pickupLocation == null || dropoffLocation == null)
        {
            throw new InvalidOperationException("Rider, pickup, and dropoff locations are required to build a trip.");
        }
        return new Trip(this);
    }

    internal string Id => id;
    internal Rider Rider => rider;
    internal Location PickupLocation => pickupLocation;
    internal Location DropoffLocation => dropoffLocation;
    internal double Fare => fare;
}