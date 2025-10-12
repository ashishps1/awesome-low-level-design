from player_status import PlayerStatus
from playable import Playable, Song
from typing import List, Optional
from player_states import PlayerState, StoppedState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class Player:
    def __init__(self):
        self._state = StoppedState()
        self._status = PlayerStatus.STOPPED
        self._queue: List[Song] = []
        self._current_index = -1
        self._current_song: Optional[Song] = None
        self._current_user: Optional[User] = None
    
    def load(self, playable: Playable, user: 'User'):
        self._current_user = user
        self._queue = playable.get_tracks()
        self._current_index = 0
        print(f"Loaded {len(self._queue)} tracks for user {user.get_name()}.")
        self._state = StoppedState()
    
    def play_current_song_in_queue(self):
        if 0 <= self._current_index < len(self._queue):
            song_to_play = self._queue[self._current_index]
            self._current_user.playback_strategy.play(song_to_play, self)
    
    def click_play(self):
        self._state.play(self)
    
    def click_pause(self):
        self._state.pause(self)
    
    def click_next(self):
        if self._current_index < len(self._queue) - 1:
            self._current_index += 1
            self.play_current_song_in_queue()
        else:
            print("End of queue.")
            self._state.stop(self)
    
    def change_state(self, state: PlayerState):
        self._state = state
    
    def set_status(self, status: PlayerStatus):
        self._status = status
    
    def set_current_song(self, song: Song):
        self._current_song = song
    
    def has_queue(self) -> bool:
        return len(self._queue) > 0