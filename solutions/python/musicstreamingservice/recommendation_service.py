from recommendation_strategy import RecommendationStrategy
from playable import Song
from typing import List

class RecommendationService:
    def __init__(self, strategy: RecommendationStrategy):
        self._strategy = strategy
    
    def set_strategy(self, strategy: RecommendationStrategy):
        self._strategy = strategy
    
    def generate_recommendations(self, all_songs: List[Song]) -> List[Song]:
        return self._strategy.recommend(all_songs)