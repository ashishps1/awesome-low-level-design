class NearestDriverMatchingStrategy : IDriverMatchingStrategy
{
    private const double MAX_DISTANCE_KM = 5.0;

    public List<Driver> FindDrivers(List<Driver> allDrivers, Location pickupLocation, RideType rideType)
    {
        Console.WriteLine($"Finding nearest drivers for ride type: {rideType}");

        return allDrivers
            .Where(driver => driver.Status == DriverStatus.ONLINE)
            .Where(driver => driver.Vehicle.Type == rideType)
            .Where(driver => pickupLocation.DistanceTo(driver.CurrentLocation) <= MAX_DISTANCE_KM)
            .OrderBy(driver => pickupLocation.DistanceTo(driver.CurrentLocation))
            .ToList();
    }
}