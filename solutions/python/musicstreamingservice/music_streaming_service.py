from music_library import MusicLibrary
from user_manager import UserManager
from music_recommender import MusicRecommender

class MusicStreamingService:
    def __init__(self):
        self.music_library = MusicLibrary.get_instance()
        self.user_manager = UserManager.get_instance()
        self.music_recommender = MusicRecommender.get_instance()

    def start(self):
        pass

    def get_music_library(self):
        return self.music_library
    
    def get_user_manager(self):
        return self.user_manager
    
    def get_music_recommender(self):
        return self.music_recommender    