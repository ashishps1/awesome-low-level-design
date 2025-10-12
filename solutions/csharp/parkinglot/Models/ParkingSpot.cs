class ParkingSpot
{
    private readonly string spotId;
    private readonly VehicleSize spotSize;
    private bool isOccupied;
    private Vehicle parkedVehicle;
    private readonly object lockObject = new object();

    public ParkingSpot(string spotId, VehicleSize spotSize)
    {
        this.spotId = spotId;
        this.spotSize = spotSize;
        this.isOccupied = false;
        this.parkedVehicle = null;
    }

    public string GetSpotId()
    {
        return spotId;
    }

    public VehicleSize GetSpotSize()
    {
        return spotSize;
    }

    public bool IsAvailable()
    {
        lock (lockObject)
        {
            return !isOccupied;
        }
    }

    public bool IsOccupiedSpot()
    {
        return isOccupied;
    }

    public void ParkVehicle(Vehicle vehicle)
    {
        lock (lockObject)
        {
            this.parkedVehicle = vehicle;
            this.isOccupied = true;
        }
    }

    public void UnparkVehicle()
    {
        lock (lockObject)
        {
            this.parkedVehicle = null;
            this.isOccupied = false;
        }
    }

    public bool CanFitVehicle(Vehicle vehicle)
    {
        if (isOccupied) return false;

        switch (vehicle.GetSize())
        {
            case VehicleSize.SMALL:
                return spotSize == VehicleSize.SMALL;
            case VehicleSize.MEDIUM:
                return spotSize == VehicleSize.MEDIUM || spotSize == VehicleSize.LARGE;
            case VehicleSize.LARGE:
                return spotSize == VehicleSize.LARGE;
            default:
                return false;
        }
    }
}