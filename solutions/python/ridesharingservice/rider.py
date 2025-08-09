from user import User
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from trip import Trip

class Rider(User):
    def __init__(self, name: str, contact: str):
        super().__init__(name, contact)
    
    def on_update(self, trip: 'Trip'):
        print(f"--- Notification for Rider {self.get_name()} ---")
        print(f"  Trip {trip.get_id()} is now {trip.get_status().value}.")
        if trip.get_driver() is not None:
            print(f"  Driver: {trip.get_driver().get_name()} in a {trip.get_driver().get_vehicle().get_model()} "
                  f"({trip.get_driver().get_vehicle().get_license_number()})")
        print("--------------------------------\n")