class RideSharingService
{
    private static volatile RideSharingService instance;
    private static readonly object lockObject = new object();
    
    private readonly Dictionary<string, Rider> riders = new Dictionary<string, Rider>();
    private readonly Dictionary<string, Driver> drivers = new Dictionary<string, Driver>();
    private readonly Dictionary<string, Trip> trips = new Dictionary<string, Trip>();
    private IPricingStrategy pricingStrategy;
    private IDriverMatchingStrategy driverMatchingStrategy;

    private RideSharingService() { }

    public static RideSharingService Instance
    {
        get
        {
            if (instance == null)
            {
                lock (lockObject)
                {
                    if (instance == null)
                    {
                        instance = new RideSharingService();
                    }
                }
            }
            return instance;
        }
    }

    public void SetPricingStrategy(IPricingStrategy strategy)
    {
        pricingStrategy = strategy;
    }

    public void SetDriverMatchingStrategy(IDriverMatchingStrategy strategy)
    {
        driverMatchingStrategy = strategy;
    }

    public Rider RegisterRider(string name, string contact)
    {
        var rider = new Rider(name, contact);
        riders[rider.Id] = rider;
        return rider;
    }

    public Driver RegisterDriver(string name, string contact, Vehicle vehicle, Location initialLocation)
    {
        var driver = new Driver(name, contact, vehicle, initialLocation);
        drivers[driver.Id] = driver;
        return driver;
    }

    public Trip RequestRide(string riderId, Location pickup, Location dropoff, RideType rideType)
    {
        if (!riders.TryGetValue(riderId, out Rider rider))
        {
            throw new ArgumentException("Rider not found");
        }

        Console.WriteLine($"\n--- New Ride Request from {rider.Name} ---");

        // 1. Find available drivers
        var availableDrivers = driverMatchingStrategy.FindDrivers(drivers.Values.ToList(), pickup, rideType);

        if (!availableDrivers.Any())
        {
            Console.WriteLine("No drivers available for your request. Please try again later.");
            return null;
        }

        Console.WriteLine($"Found {availableDrivers.Count} available driver(s).");

        // 2. Calculate fare
        double fare = pricingStrategy.CalculateFare(pickup, dropoff, rideType);
        Console.WriteLine($"Estimated fare: ${fare:F2}");

        // 3. Create a trip using the Builder
        var trip = new TripBuilder()
            .WithRider(rider)
            .WithPickupLocation(pickup)
            .WithDropoffLocation(dropoff)
            .WithFare(fare)
            .Build();

        trips[trip.Id] = trip;

        // 4. Notify nearby drivers
        Console.WriteLine("Notifying nearby drivers of the new ride request...");
        foreach (var driver in availableDrivers)
        {
            Console.WriteLine($" > Notifying {driver.Name} at {driver.CurrentLocation}");
            driver.OnUpdate(trip);
        }

        return trip;
    }

    public void AcceptRide(string driverId, string tripId)
    {
        if (!drivers.TryGetValue(driverId, out Driver driver) || !trips.TryGetValue(tripId, out Trip trip))
        {
            throw new ArgumentException("Driver or Trip not found");
        }

        Console.WriteLine($"\n--- Driver {driver.Name} accepted the ride ---");

        driver.SetStatus(DriverStatus.IN_TRIP);
        trip.AssignDriver(driver);
    }

    public void StartTrip(string tripId)
    {
        if (!trips.TryGetValue(tripId, out Trip trip))
        {
            throw new ArgumentException("Trip not found");
        }
        Console.WriteLine($"\n--- Trip {trip.Id} is starting ---");
        trip.StartTrip();
    }

    public void EndTrip(string tripId)
    {
        if (!trips.TryGetValue(tripId, out Trip trip))
        {
            throw new ArgumentException("Trip not found");
        }
        Console.WriteLine($"\n--- Trip {trip.Id} is ending ---");
        trip.EndTrip();

        // Update statuses and history
        var driver = trip.Driver;
        driver.SetStatus(DriverStatus.ONLINE);
        driver.SetCurrentLocation(trip.DropoffLocation);

        var rider = trip.Rider;
        driver.AddTripToHistory(trip);
        rider.AddTripToHistory(trip);

        Console.WriteLine($"Driver {driver.Name} is now back online at {driver.CurrentLocation}");
    }
}