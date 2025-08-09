from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from trip import Trip

class TripObserver(ABC):
    @abstractmethod
    def on_update(self, trip: 'Trip'):
        pass