from abc import ABC, abstractmethod
from typing import List
from playable import Song
import random

class RecommendationStrategy(ABC):
    @abstractmethod
    def recommend(self, all_songs: List[Song]) -> List[Song]:
        pass

class GenreBasedRecommendationStrategy(RecommendationStrategy):
    def recommend(self, all_songs: List[Song]) -> List[Song]:
        print("Generating genre-based recommendations (simulated)...")
        shuffled = all_songs.copy()
        random.shuffle(shuffled)
        return shuffled[:5]