class SearchByCityStrategy : IRestaurantSearchStrategy
{
    private readonly string city;

    public SearchByCityStrategy(string city)
    {
        this.city = city;
    }

    public List<Restaurant> Filter(List<Restaurant> allRestaurants)
    {
        return allRestaurants
            .Where(r => r.GetAddress().GetCity().Equals(city, StringComparison.OrdinalIgnoreCase))
            .ToList();
    }
}