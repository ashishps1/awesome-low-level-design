package movieticketbookingsystem;

import movieticketbookingsystem.booking.Booking;
import movieticketbookingsystem.booking.BookingStatus;
import movieticketbookingsystem.seat.Seat;
import movieticketbookingsystem.seat.SeatStatus;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

public class MovieTicketBookingSystem {
    private static MovieTicketBookingSystem instance;
    private final List<Movie> movies;
    private final List<Theater> theaters;
    private final Map<String, Show> shows;
    private final Map<String, Booking> bookings;

    private static final String BOOKING_ID_PREFIX = "BKG";
    private static final AtomicLong bookingCounter = new AtomicLong(0);

    private MovieTicketBookingSystem() {
        movies = new ArrayList<>();
        theaters = new ArrayList<>();
        shows = new ConcurrentHashMap<>();
        bookings = new ConcurrentHashMap<>();
    }

    public static synchronized MovieTicketBookingSystem getInstance() {
        if (instance == null) {
            instance = new MovieTicketBookingSystem();
        }
        return instance;
    }

    public void addMovie(Movie movie) {
        movies.add(movie);
    }

    public void addTheater(Theater theater) {
        theaters.add(theater);
    }

    public void addShow(Show show) {
        shows.put(show.getId(), show);
    }

    public List<Movie> getMovies() {
        return movies;
    }

    public List<Theater> getTheaters() {
        return theaters;
    }

    public Show getShow(String showId) {
        return shows.get(showId);
    }

    public synchronized Booking bookTickets(User user, Show show, List<Seat> selectedSeats) {
        if (areSeatsAvailable(show, selectedSeats)) {
            markSeatsAsBooked(show, selectedSeats);
            double totalPrice = calculateTotalPrice(selectedSeats);
            String bookingId = generateBookingId();
            Booking booking = new Booking(bookingId, user, show, selectedSeats, totalPrice, BookingStatus.PENDING);
            bookings.put(bookingId, booking);
            return booking;
        }
        return null;
    }

    private boolean areSeatsAvailable(Show show, List<Seat> selectedSeats) {
        for (Seat seat : selectedSeats) {
            Seat showSeat = show.getSeats().get(seat.getId());
            if (showSeat == null || showSeat.getStatus() != SeatStatus.AVAILABLE) {
                return false;
            }
        }
        return true;
    }

    private void markSeatsAsBooked(Show show, List<Seat> selectedSeats) {
        for (Seat seat : selectedSeats) {
            Seat showSeat = show.getSeats().get(seat.getId());
            showSeat.setStatus(SeatStatus.BOOKED);
        }
    }

    private double calculateTotalPrice(List<Seat> selectedSeats) {
        return selectedSeats.stream().mapToDouble(Seat::getPrice).sum();
    }

    private String generateBookingId() {
        long bookingNumber = bookingCounter.incrementAndGet();
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyyMMddHHmmss"));
        return BOOKING_ID_PREFIX + timestamp + String.format("%06d", bookingNumber);
    }

    public synchronized void confirmBooking(String bookingId) {
        Booking booking = bookings.get(bookingId);
        if (booking != null && booking.getStatus() == BookingStatus.PENDING) {
            booking.setStatus(BookingStatus.CONFIRMED);
            // Process payment and send confirmation
            // ...
        }
    }

    public synchronized void cancelBooking(String bookingId) {
        Booking booking = bookings.get(bookingId);
        if (booking != null && booking.getStatus() != BookingStatus.CANCELLED) {
            booking.setStatus(BookingStatus.CANCELLED);
            markSeatsAsAvailable(booking.getShow(), booking.getSeats());
            // Process refund and send cancellation notification
            // ...
        }
    }

    private void markSeatsAsAvailable(Show show, List<Seat> seats) {
        for (Seat seat : seats) {
            Seat showSeat = show.getSeats().get(seat.getId());
            showSeat.setStatus(SeatStatus.AVAILABLE);
        }
    }
}
