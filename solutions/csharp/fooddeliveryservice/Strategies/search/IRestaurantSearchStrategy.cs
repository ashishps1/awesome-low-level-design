interface IRestaurantSearchStrategy
{
    List<Restaurant> Filter(List<Restaurant> allRestaurants);
}