package ridehailingservice.state;

import ridehailingservice.entities.Driver;
import ridehailingservice.entities.Trip;
import ridehailingservice.enums.TripStatus;

public class InProgressState implements TripState {
    @Override
    public void request(Trip trip) {
        System.out.println("Trip is already in progress.");
    }

    @Override
    public void assign(Trip trip, Driver driver) {
        System.out.println("Cannot assign a new driver while trip is in progress.");
    }

    @Override
    public void start(Trip trip) {
        System.out.println("Trip is already in progress.");
    }

    @Override
    public void end(Trip trip) {
        trip.setStatus(TripStatus.COMPLETED);
        trip.setState(new CompletedState());
    }
}
