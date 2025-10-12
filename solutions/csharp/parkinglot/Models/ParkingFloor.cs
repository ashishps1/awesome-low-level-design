class ParkingFloor
{
    private readonly int floorNumber;
    private readonly Dictionary<string, ParkingSpot> spots;
    private readonly object lockObject = new object();

    public ParkingFloor(int floorNumber)
    {
        this.floorNumber = floorNumber;
        this.spots = new Dictionary<string, ParkingSpot>();
    }

    public void AddSpot(ParkingSpot spot)
    {
        spots[spot.GetSpotId()] = spot;
    }

    public ParkingSpot FindAvailableSpot(Vehicle vehicle)
    {
        lock (lockObject)
        {
            var availableSpots = spots.Values
                .Where(spot => !spot.IsOccupiedSpot() && spot.CanFitVehicle(vehicle))
                .OrderBy(spot => (int)spot.GetSpotSize())
                .ToList();

            return availableSpots.FirstOrDefault();
        }
    }

    public void DisplayAvailability()
    {
        Console.WriteLine($"--- Floor {floorNumber} Availability ---");
        var availableCounts = new Dictionary<VehicleSize, int>
        {
            { VehicleSize.SMALL, 0 },
            { VehicleSize.MEDIUM, 0 },
            { VehicleSize.LARGE, 0 }
        };

        foreach (var spot in spots.Values)
        {
            if (!spot.IsOccupiedSpot())
            {
                availableCounts[spot.GetSpotSize()]++;
            }
        }

        foreach (VehicleSize size in Enum.GetValues(typeof(VehicleSize)))
        {
            Console.WriteLine($"  {size} spots: {availableCounts[size]}");
        }
    }
}