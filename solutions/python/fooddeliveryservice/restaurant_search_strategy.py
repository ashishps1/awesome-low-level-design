from abc import ABC, abstractmethod
from typing import List
from restaurant import Restaurant
from address import Address

class RestaurantSearchStrategy(ABC):
    @abstractmethod
    def filter(self, all_restaurants: List[Restaurant]) -> List[Restaurant]:
        pass

class SearchByCityStrategy(RestaurantSearchStrategy):
    def __init__(self, city: str):
        self.city = city

    def filter(self, all_restaurants: List[Restaurant]) -> List[Restaurant]:
        return [r for r in all_restaurants if r.get_address().get_city().lower() == self.city.lower()]

class SearchByMenuKeywordStrategy(RestaurantSearchStrategy):
    def __init__(self, keyword: str):
        self.keyword = keyword.lower()

    def filter(self, all_restaurants: List[Restaurant]) -> List[Restaurant]:
        result = []
        for r in all_restaurants:
            for item in r.get_menu().get_items().values():
                if self.keyword in item.get_name().lower():
                    result.append(r)
                    break
        return result

class SearchByProximityStrategy(RestaurantSearchStrategy):
    def __init__(self, user_location: Address, max_distance: float):
        self.user_location = user_location
        self.max_distance = max_distance

    def filter(self, all_restaurants: List[Restaurant]) -> List[Restaurant]:
        filtered = [r for r in all_restaurants if self.user_location.distance_to(r.get_address()) <= self.max_distance]
        filtered.sort(key=lambda r: self.user_location.distance_to(r.get_address()))
        return filtered