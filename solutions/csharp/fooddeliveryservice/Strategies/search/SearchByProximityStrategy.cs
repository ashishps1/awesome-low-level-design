class SearchByProximityStrategy : IRestaurantSearchStrategy
{
    private readonly Address userLocation;
    private readonly double maxDistance;

    public SearchByProximityStrategy(Address userLocation, double maxDistance)
    {
        this.userLocation = userLocation;
        this.maxDistance = maxDistance;
    }

    public List<Restaurant> Filter(List<Restaurant> allRestaurants)
    {
        return allRestaurants
            .Where(r => userLocation.DistanceTo(r.GetAddress()) <= maxDistance)
            .OrderBy(r => userLocation.DistanceTo(r.GetAddress()))
            .ToList();
    }
}