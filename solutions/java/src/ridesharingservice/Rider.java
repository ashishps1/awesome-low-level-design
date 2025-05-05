package ridesharingservice;

public class Rider extends User {
    private Trip currentTrip;

    public Rider(String name, String contact) {
        super(name, contact);
    }

    public synchronized void assignTrip(Trip trip) {
        this.currentTrip = trip;
    }

    public synchronized void completeTrip() {
        this.currentTrip = null;
    }

    public Trip getCurrentTrip() { return currentTrip; }
}