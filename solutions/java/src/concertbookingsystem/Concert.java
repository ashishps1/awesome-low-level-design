package concertbookingsystem;

import java.time.LocalDateTime;
import java.util.List;

public class Concert {
    private final String id;
    private final String artist;
    private final String venue;
    private final LocalDateTime dateTime;
    private final List<Seat> seats;

    public Concert(String id, String artist, String venue, LocalDateTime dateTime, List<Seat> seats) {
        this.id = id;
        this.artist = artist;
        this.venue = venue;
        this.dateTime = dateTime;
        this.seats = seats;
    }

    public String getId() {
        return id;
    }

    public String getArtist() {
        return artist;
    }

    public String getVenue() {
        return venue;
    }

    public LocalDateTime getDateTime() {
        return dateTime;
    }

    public List<Seat> getSeats() {
        return seats;
    }
}
