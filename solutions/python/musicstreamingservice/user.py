from observer import ArtistObserver
from typing import Set
from artist import Artist
from playable import Album
from subscription_tier import SubscriptionTier
from playback_strategy import PlaybackStrategy
import uuid

class User(ArtistObserver):
    def __init__(self, user_id: str, name: str, playback_strategy: PlaybackStrategy):
        self._id = user_id
        self._name = name
        self._playback_strategy = playback_strategy
        self._followed_artists: Set[Artist] = set()
    
    def follow_artist(self, artist: Artist):
        self._followed_artists.add(artist)
        artist.add_observer(self)
    
    def update(self, artist: Artist, new_album: Album):
        print(f"[Notification for {self._name}] Your followed artist {artist.get_name()} "
              f"just released a new album: {new_album.get_title()}!")
    
    @property
    def playback_strategy(self) -> PlaybackStrategy:
        return self._playback_strategy
    
    @property
    def id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name
    
    class Builder:
        def __init__(self, name: str):
            self._id = str(uuid.uuid4())
            self._name = name
            self._playback_strategy = None
        
        def with_subscription(self, tier: SubscriptionTier, songs_played: int) -> 'User.Builder':
            self._playback_strategy = PlaybackStrategy.get_strategy(tier, songs_played)
            return self
        
        def build(self) -> 'User':
            return User(self._id, self._name, self._playback_strategy)