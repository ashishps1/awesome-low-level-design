from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from event import Event

class PostObserver(ABC):
    @abstractmethod
    def on_post_event(self, event: 'Event'):
        pass