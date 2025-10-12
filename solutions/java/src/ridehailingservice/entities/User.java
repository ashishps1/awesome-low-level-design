package ridehailingservice.entities;

import ridehailingservice.observer.TripObserver;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public abstract class User implements TripObserver {
    private final String id;
    private final String name;
    private final String contact;
    private final List<Trip> tripHistory;

    public User(String name, String contact) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.contact = contact;
        this.tripHistory = new ArrayList<>();
    }

    public void addTripToHistory(Trip trip) {
        tripHistory.add(trip);
    }

    public List<Trip> getTripHistory() {
        return tripHistory;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getContact() {
        return contact;
    }
}
