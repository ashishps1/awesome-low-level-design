package ridesharingservice.observer;

import ridesharingservice.entities.Trip;

public interface TripObserver {
    void onUpdate(Trip trip);
}
