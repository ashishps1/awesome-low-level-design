interface IDriverMatchingStrategy
{
    List<Driver> FindDrivers(List<Driver> allDrivers, Location pickupLocation, RideType rideType);
}