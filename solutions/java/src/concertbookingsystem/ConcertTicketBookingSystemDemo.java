package concertbookingsystem;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class ConcertTicketBookingSystemDemo {
    public static void run() {
        // Create concert ticket booking system instance
        ConcertTicketBookingSystem bookingSystem = ConcertTicketBookingSystem.getInstance();

        // Create concerts
        List<Seat> concert1Seats = generateSeats(100);
        Concert concert1 = new Concert("C001", "Artist 1", "Venue 1", LocalDateTime.now().plusDays(30), concert1Seats);
        bookingSystem.addConcert(concert1);

        List<Seat> concert2Seats = generateSeats(50);
        Concert concert2 = new Concert("C002", "Artist 2", "Venue 2", LocalDateTime.now().plusDays(60), concert2Seats);
        bookingSystem.addConcert(concert2);

        // Create users
        User user1 = new User("U001", "John Doe", "john@example.com");
        User user2 = new User("U002", "Jane Smith", "jane@example.com");

        // Search concerts
        List<Concert> searchResults = bookingSystem.searchConcerts("Artist 1", "Venue 1", LocalDateTime.now().plusDays(30));
        System.out.println("Search Results:");
        for (Concert concert : searchResults) {
            System.out.println("Concert: " + concert.getArtist() + " at " + concert.getVenue());
        }

        // Book tickets
        List<Seat> selectedSeats1 = selectSeats(concert1, 3);
        Booking booking1 = bookingSystem.bookTickets(user1, concert1, selectedSeats1);

        List<Seat> selectedSeats2 = selectSeats(concert2, 2);
        Booking booking2 = bookingSystem.bookTickets(user2, concert2, selectedSeats2);

        // Cancel booking
        bookingSystem.cancelBooking(booking1.getId());

        // Book tickets again
        List<Seat> selectedSeats3 = selectSeats(concert1, 2);
        Booking booking3 = bookingSystem.bookTickets(user2, concert1, selectedSeats3);
    }

    private static List<Seat> generateSeats(int numberOfSeats) {
        List<Seat> seats = new ArrayList<>();
        for (int i = 1; i <= numberOfSeats; i++) {
            String seatNumber = "S" + i;
            SeatType seatType = (i <= 10) ? SeatType.VIP : (i <= 30) ? SeatType.PREMIUM : SeatType.REGULAR;
            double price = (seatType == SeatType.VIP) ? 100.0 : (seatType == SeatType.PREMIUM) ? 75.0 : 50.0;
            seats.add(new Seat(seatNumber, seatNumber, seatType, price));
        }
        return seats;
    }

    private static List<Seat> selectSeats(Concert concert, int numberOfSeats) {
        List<Seat> selectedSeats = new ArrayList<>();
        List<Seat> availableSeats = concert.getSeats().stream()
                .filter(seat -> seat.getStatus() == SeatStatus.AVAILABLE)
                .limit(numberOfSeats)
                .toList();
        selectedSeats.addAll(availableSeats);
        return selectedSeats;
    }
}
