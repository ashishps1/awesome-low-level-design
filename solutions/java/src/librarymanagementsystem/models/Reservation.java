package librarymanagementsystem.models;

import java.time.LocalDateTime;
import java.util.UUID;

/**
 * Represents a book reservation.
 * Follows SRP - Only handles reservation data
 */
public class Reservation {
    private final String reservationId;
    private final String isbn;
    private final String patronId;
    private final LocalDateTime reservationDate;
    private LocalDateTime expirationDate;
    private ReservationStatus status;
    
    public enum ReservationStatus {
        ACTIVE,
        FULFILLED,
        EXPIRED,
        CANCELLED
    }
    
    public Reservation(String isbn, String patronId) {
        this.reservationId = UUID.randomUUID().toString();
        this.isbn = isbn;
        this.patronId = patronId;
        this.reservationDate = LocalDateTime.now();
        this.expirationDate = reservationDate.plusDays(7); // 7 days to pick up
        this.status = ReservationStatus.ACTIVE;
    }
    
    // Getters
    public String getReservationId() { return reservationId; }
    public String getIsbn() { return isbn; }
    public String getPatronId() { return patronId; }
    public LocalDateTime getReservationDate() { return reservationDate; }
    public LocalDateTime getExpirationDate() { return expirationDate; }
    public ReservationStatus getStatus() { return status; }
    
    // Business methods
    public void fulfill() {
        this.status = ReservationStatus.FULFILLED;
    }
    
    public void cancel() {
        this.status = ReservationStatus.CANCELLED;
    }
    
    public void expire() {
        this.status = ReservationStatus.EXPIRED;
    }
    
    public boolean isActive() {
        return status == ReservationStatus.ACTIVE && 
               LocalDateTime.now().isBefore(expirationDate);
    }
    
    @Override
    public String toString() {
        return String.format("Reservation{id='%s', isbn='%s', patron='%s', status=%s}",
                reservationId, isbn, patronId, status);
    }
}