from abc import ABC, abstractmethod
from player_status import PlayerStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from player import Player

class PlayerState(ABC):
    @abstractmethod
    def play(self, player: 'Player'):
        pass
    
    @abstractmethod
    def pause(self, player: 'Player'):
        pass
    
    @abstractmethod
    def stop(self, player: 'Player'):
        pass

class PausedState(PlayerState):
    def play(self, player: 'Player'):
        print("Resuming playback.")
        player.change_state(PlayingState())
        player.set_status(PlayerStatus.PLAYING)
    
    def pause(self, player: 'Player'):
        print("Already paused.")
    
    def stop(self, player: 'Player'):
        print("Stopping playback from paused state.")
        player.change_state(StoppedState())
        player.set_status(PlayerStatus.STOPPED)

class PlayingState(PlayerState):
    def play(self, player: 'Player'):
        print("Already playing.")
    
    def pause(self, player: 'Player'):
        print("Pausing playback.")
        player.change_state(PausedState())
        player.set_status(PlayerStatus.PAUSED)
    
    def stop(self, player: 'Player'):
        print("Stopping playback.")
        player.change_state(StoppedState())
        player.set_status(PlayerStatus.STOPPED)

class StoppedState(PlayerState):
    def play(self, player: 'Player'):
        if player.has_queue():
            print("Starting playback.")
            player.change_state(PlayingState())
            player.set_status(PlayerStatus.PLAYING)
            player.play_current_song_in_queue()
        else:
            print("Queue is empty. Load songs to play.")
    
    def pause(self, player: 'Player'):
        print("Cannot pause. Player is stopped.")
    
    def stop(self, player: 'Player'):
        print("Already stopped.")