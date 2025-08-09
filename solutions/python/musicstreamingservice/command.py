from abc import ABC, abstractmethod
from player import Player

class Command(ABC):
    @abstractmethod
    def execute(self):
        pass

class PlayCommand(Command):
    def __init__(self, player: Player):
        self._player = player
    
    def execute(self):
        self._player.click_play()

class PauseCommand(Command):
    def __init__(self, player: Player):
        self._player = player
    
    def execute(self):
        self._player.click_pause()

class NextTrackCommand(Command):
    def __init__(self, player: Player):
        self._player = player
    
    def execute(self):
        self._player.click_next()