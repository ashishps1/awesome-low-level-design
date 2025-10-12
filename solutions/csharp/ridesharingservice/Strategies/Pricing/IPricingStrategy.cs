interface IPricingStrategy
{
    double CalculateFare(Location pickup, Location dropoff, RideType rideType);
}