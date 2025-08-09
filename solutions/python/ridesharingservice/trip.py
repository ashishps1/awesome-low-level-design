from typing import Optional, List
from enums import TripStatus
from trip_states import TripState, RequestedState
from rider import Rider
from trip_observer import TripObserver
from location import Location
import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from driver import Driver

class Trip:
    def __init__(self, builder: 'TripBuilder'):
        self._id = builder._id
        self._rider = builder._rider
        self._driver: Optional['Driver'] = None
        self._pickup_location = builder._pickup_location
        self._dropoff_location = builder._dropoff_location
        self._fare = builder._fare
        self._status = TripStatus.REQUESTED
        self._current_state = RequestedState()  # Initial state
        self._observers: List[TripObserver] = []
    
    def add_observer(self, observer: TripObserver):
        self._observers.append(observer)
    
    def _notify_observers(self):
        for observer in self._observers:
            observer.on_update(self)
    
    def assign_driver(self, driver: 'Driver'):
        self._current_state.assign(self, driver)
        self.add_observer(driver)
        self._notify_observers()
    
    def start_trip(self):
        self._current_state.start(self)
        self._notify_observers()
    
    def end_trip(self):
        self._current_state.end(self)
        self._notify_observers()
    
    # Getters
    def get_id(self) -> str:
        return self._id
    
    def get_rider(self) -> Rider:
        return self._rider
    
    def get_driver(self) -> Optional['Driver']:
        return self._driver
    
    def get_pickup_location(self) -> Location:
        return self._pickup_location
    
    def get_dropoff_location(self) -> Location:
        return self._dropoff_location
    
    def get_fare(self) -> float:
        return self._fare
    
    def get_status(self) -> TripStatus:
        return self._status
    
    # Setters are protected, only to be called by State objects
    def set_state(self, state: TripState):
        self._current_state = state
    
    def set_status(self, status: TripStatus):
        self._status = status
    
    def set_driver(self, driver: 'Driver'):
        self._driver = driver
    
    def __str__(self) -> str:
        return f"Trip [id={self._id}, status={self._status.value}, fare=${self._fare:.2f}]"
    
    # Builder Pattern
    class TripBuilder:
        def __init__(self):
            self._id = str(uuid.uuid4())
            self._rider: Optional[Rider] = None
            self._pickup_location: Optional[Location] = None
            self._dropoff_location: Optional[Location] = None
            self._fare = 0.0
        
        def with_rider(self, rider: Rider) -> 'Trip.TripBuilder':
            self._rider = rider
            return self
        
        def with_pickup_location(self, pickup_location: Location) -> 'Trip.TripBuilder':
            self._pickup_location = pickup_location
            return self
        
        def with_dropoff_location(self, dropoff_location: Location) -> 'Trip.TripBuilder':
            self._dropoff_location = dropoff_location
            return self
        
        def with_fare(self, fare: float) -> 'Trip.TripBuilder':
            self._fare = fare
            return self
        
        def build(self) -> 'Trip':
            # Basic validation
            if self._rider is None or self._pickup_location is None or self._dropoff_location is None:
                raise ValueError("Rider, pickup, and dropoff locations are required to build a trip.")
            return Trip(self)