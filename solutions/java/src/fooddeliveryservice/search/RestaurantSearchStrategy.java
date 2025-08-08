package fooddeliveryservice.search;

import fooddeliveryservice.entity.Restaurant;

import java.util.List;

public interface RestaurantSearchStrategy {
    List<Restaurant> filter(List<Restaurant> allRestaurants);
}
