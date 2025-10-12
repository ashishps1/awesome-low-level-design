class VehicleBasedPricingStrategy : IPricingStrategy
{
    private const double BASE_FARE = 2.50;
    private readonly Dictionary<RideType, double> ratePerKm = new Dictionary<RideType, double>
    {
        { RideType.SEDAN, 1.50 },
        { RideType.SUV, 2.00 },
        { RideType.AUTO, 1.00 }
    };

    public double CalculateFare(Location pickup, Location dropoff, RideType rideType)
    {
        return BASE_FARE + ratePerKm[rideType] * pickup.DistanceTo(dropoff);
    }
}