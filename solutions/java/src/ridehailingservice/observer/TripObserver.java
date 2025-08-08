package ridehailingservice.observer;

import ridehailingservice.entities.Trip;

public interface TripObserver {
    void onUpdate(Trip trip);
}
