package ridesharingservice.state;

import ridesharingservice.entities.Driver;
import ridesharingservice.entities.Trip;

public interface TripState {
    void request(Trip trip);
    void assign(Trip trip, Driver driver);
    void start(Trip trip);
    void end(Trip trip);
}
