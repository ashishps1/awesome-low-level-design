package airlinemanagementsystem;

public class Aircraft {
    private final String tailNumber;
    private final String model;
    private final int totalSeats;

    public Aircraft(String tailNumber, String model, int totalSeats) {
        this.tailNumber = tailNumber;
        this.model = model;
        this.totalSeats = totalSeats;
    }
}
