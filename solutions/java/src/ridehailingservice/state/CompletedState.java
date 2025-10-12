package ridehailingservice.state;

import ridehailingservice.entities.Driver;
import ridehailingservice.entities.Trip;

public class CompletedState implements TripState {
    @Override
    public void request(Trip trip) {
        System.out.println("Cannot request a trip that is already completed.");
    }

    @Override
    public void assign(Trip trip, Driver driver) {
        System.out.println("Cannot assign a driver to a completed trip.");
    }

    @Override
    public void start(Trip trip) {
        System.out.println("Cannot start a completed trip.");
    }

    @Override
    public void end(Trip trip) {
        System.out.println("Trip is already completed.");
    }
}
