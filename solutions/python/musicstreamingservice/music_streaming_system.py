import threading
from typing import Dict, List
from user import User
from playable import Song
from artist import Artist
from player import Player
from search_service import SearchService
from recommendation_service import RecommendationService
from recommendation_strategy import GenreBasedRecommendationStrategy

class MusicStreamingSystem:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._users: Dict[str, User] = {}
            self._songs: Dict[str, Song] = {}
            self._artists: Dict[str, Artist] = {}
            self._player = Player()
            self._search_service = SearchService()
            self._recommendation_service = RecommendationService(GenreBasedRecommendationStrategy())
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def register_user(self, user: User):
        self._users[user.id] = user
    
    def add_song(self, song_id: str, title: str, artist_id: str, duration: int) -> Song:
        song = Song(song_id, title, self._artists[artist_id], duration)
        self._songs[song.id] = song
        return song
    
    def add_artist(self, artist: Artist):
        self._artists[artist.id] = artist
    
    def search_songs_by_title(self, title: str) -> List[Song]:
        return self._search_service.search_songs_by_title(list(self._songs.values()), title)
    
    def get_song_recommendations(self) -> List[Song]:
        return self._recommendation_service.generate_recommendations(list(self._songs.values()))
    
    def get_player(self) -> Player:
        return self._player