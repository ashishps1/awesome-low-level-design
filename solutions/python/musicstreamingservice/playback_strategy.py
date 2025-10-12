from abc import ABC, abstractmethod
from subscription_tier import SubscriptionTier
from playable import Song
from player import Player
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from player import Player

class PlaybackStrategy(ABC):
    @abstractmethod
    def play(self, song: Song, player: 'Player'):
        pass
    
    @staticmethod
    def get_strategy(tier: SubscriptionTier, songs_played: int) -> 'PlaybackStrategy':
        if tier == SubscriptionTier.PREMIUM:
            return PremiumPlaybackStrategy()
        else:
            return FreePlaybackStrategy(songs_played)

class FreePlaybackStrategy(PlaybackStrategy):
    SONGS_BEFORE_AD = 3
    
    def __init__(self, initial_songs_played: int):
        self._songs_played = initial_songs_played
    
    def play(self, song: Song, player: 'Player'):
        if self._songs_played > 0 and self._songs_played % self.SONGS_BEFORE_AD == 0:
            print("\n>>> Playing Advertisement: 'Buy Spotify Premium for ad-free music!' <<<\n")
        player.set_current_song(song)
        print(f"Free User is now playing: {song}")
        self._songs_played += 1

class PremiumPlaybackStrategy(PlaybackStrategy):
    def play(self, song: Song, player: 'Player'):
        player.set_current_song(song)
        print(f"Premium User is now playing: {song}")