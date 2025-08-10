class Driver : User
{
    private Vehicle vehicle;
    private Location currentLocation;
    private DriverStatus status;

    public Driver(string name, string contact, Vehicle v, Location loc)
        : base(name, contact)
    {
        vehicle = v;
        currentLocation = loc;
        status = DriverStatus.OFFLINE;
    }

    public Vehicle Vehicle => vehicle;
    public DriverStatus Status => status;

    public void SetStatus(DriverStatus s)
    {
        status = s;
        Console.WriteLine($"Driver {Name} is now {s}");
    }

    public Location CurrentLocation => currentLocation;
    
    public void SetCurrentLocation(Location loc)
    {
        currentLocation = loc;
    }

    public override void OnUpdate(Trip trip)
    {
        Console.WriteLine($"--- Notification for Driver {Name} ---");
        Console.WriteLine($"  Trip {trip.Id} status: {trip.Status}.");
        if (trip.Status == TripStatus.REQUESTED)
        {
            Console.WriteLine("  A new ride is available for you to accept.");
        }
        Console.WriteLine("--------------------------------\n");
    }
}