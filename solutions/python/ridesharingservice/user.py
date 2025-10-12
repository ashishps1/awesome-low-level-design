from typing import List
from trip_observer import TripObserver
import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from trip import Trip

class User(TripObserver):
    def __init__(self, name: str, contact: str):
        self._id = str(uuid.uuid4())
        self._name = name
        self._contact = contact
        self._trip_history: List['Trip'] = []
    
    def add_trip_to_history(self, trip: 'Trip'):
        self._trip_history.append(trip)
    
    def get_trip_history(self) -> List['Trip']:
        return self._trip_history
    
    def get_id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name
    
    def get_contact(self) -> str:
        return self._contact