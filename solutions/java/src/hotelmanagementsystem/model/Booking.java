package hotelmanagementsystem.model;

import hotelmanagementsystem.enums.BookingStatus;

import java.time.LocalDate;

public class Booking {
    private final String bookingId;
    private final Guest guest;
    private final Room room;
    private final LocalDate startDate;
    private final LocalDate endDate;
    private BookingStatus status;

    public Booking(String bookingId, Guest guest, Room room, LocalDate startDate, LocalDate endDate) {
        this.bookingId = bookingId;
        this.guest = guest;
        this.room = room;
        this.startDate = startDate;
        this.endDate = endDate;
        this.status = BookingStatus.CONFIRMED;
    }

    public void checkIn() { this.status = BookingStatus.CHECKED_IN; }
    public void checkOut() { this.status = BookingStatus.CHECKED_OUT; }
    public void cancel() { this.status = BookingStatus.CANCELLED; }

    public String getBookingId() { return bookingId; }
    public Guest getGuest() { return guest; }
    public Room getRoom() { return room; }
    public LocalDate getStartDate() { return startDate; }
    public LocalDate getEndDate() { return endDate; }
    public BookingStatus getStatus() { return status; }
}
