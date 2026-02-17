package librarymanagementsystem.services;

import librarymanagementsystem.models.Book;
import librarymanagementsystem.models.Patron;
import librarymanagementsystem.models.Reservation;
import librarymanagementsystem.repositories.BookRepository;
import librarymanagementsystem.repositories.PatronRepository;
import librarymanagementsystem.exceptions.BookNotFoundException;
import librarymanagementsystem.exceptions.PatronNotFoundException;
import librarymanagementsystem.patterns.observer.PatronObserver;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Service for book reservation operations.
 * Follows SRP - Only handles reservation logic
 * Uses Observer Pattern to notify patrons when books become available
 */
public class ReservationService {
    private final BookRepository bookRepository;
    private final PatronRepository patronRepository;
    private final NotificationService notificationService;
    private final Map<String, Queue<Reservation>> reservationQueues; // ISBN -> Queue of reservations
    
    public ReservationService(
            BookRepository bookRepository,
            PatronRepository patronRepository,
            NotificationService notificationService) {
        this.bookRepository = bookRepository;
        this.patronRepository = patronRepository;
        this.notificationService = notificationService;
        this.reservationQueues = new HashMap<>();
    }
    
    /**
     * Reserve a book for a patron.
     */
    public Reservation reserveBook(String isbn, String patronId) {
        // Validate book and patron exist
        Book book = bookRepository.findById(isbn)
                .orElseThrow(() -> new BookNotFoundException("Book not found: " + isbn));
        
        Patron patron = patronRepository.findById(patronId)
                .orElseThrow(() -> new PatronNotFoundException("Patron not found: " + patronId));
        
        // Check if book is available
        if (book.isAvailable()) {
            throw new IllegalStateException("Book is currently available. Please checkout directly.");
        }
        
        // Check if patron already has a reservation for this book
        Queue<Reservation> queue = reservationQueues.getOrDefault(isbn, new LinkedList<>());
        boolean alreadyReserved = queue.stream()
                .anyMatch(r -> r.getPatronId().equals(patronId) && r.isActive());
        
        if (alreadyReserved) {
            throw new IllegalStateException("Patron already has an active reservation for this book");
        }
        
        // Create reservation
        Reservation reservation = new Reservation(isbn, patronId);
        
        // Add to queue
        if (!reservationQueues.containsKey(isbn)) {
            reservationQueues.put(isbn, new LinkedList<>());
        }
        reservationQueues.get(isbn).offer(reservation);
        
        // Attach patron as observer
        PatronObserver observer = new PatronObserver(patron);
        notificationService.attach(observer);
        
        // Mark book as reserved
        book.markAsReserved();
        bookRepository.save(book);
        
        System.out.println("✅ Book reserved: " + book.getTitle() + " for " + patron.getName());
        System.out.println("   Position in queue: " + reservationQueues.get(isbn).size());
        
        return reservation;
    }
    
    /**
     * Cancel a reservation.
     */
    public void cancelReservation(String isbn, String patronId) {
        Queue<Reservation> queue = reservationQueues.get(isbn);
        if (queue == null) {
            throw new IllegalStateException("No reservations found for this book");
        }
        
        Reservation toCancel = queue.stream()
                .filter(r -> r.getPatronId().equals(patronId) && r.isActive())
                .findFirst()
                .orElseThrow(() -> new IllegalStateException("No active reservation found"));
        
        toCancel.cancel();
        queue.remove(toCancel);
        
        System.out.println("✅ Reservation cancelled for patron: " + patronId);
    }
    
    /**
     * Process book return and notify next patron in queue.
     */
    public void processBookReturn(String isbn) {
        Queue<Reservation> queue = reservationQueues.get(isbn);
        
        if (queue == null || queue.isEmpty()) {
            System.out.println("ℹ️ No reservations for this book");
            return;
        }
        
        // Get next reservation in queue
        Reservation nextReservation = queue.peek();
        
        while (nextReservation != null && !nextReservation.isActive()) {
            // Remove expired/cancelled reservations
            queue.poll();
            nextReservation = queue.peek();
        }
        
        if (nextReservation != null) {
            // Notify patron
            Patron patron = patronRepository.findById(nextReservation.getPatronId())
                    .orElse(null);
            
            if (patron != null) {
                Book book = bookRepository.findById(isbn).orElse(null);
                String bookTitle = book != null ? book.getTitle() : "Unknown";
                
                notificationService.notifyBookAvailable(bookTitle);
                
                System.out.println("📢 Notified patron: " + patron.getName() + 
                                 " - Book available: " + bookTitle);
            }
        }
    }
    
    /**
     * Get all reservations for a book.
     */
    public List<Reservation> getReservationsForBook(String isbn) {
        Queue<Reservation> queue = reservationQueues.get(isbn);
        return queue != null ? new ArrayList<>(queue) : new ArrayList<>();
    }
    
    /**
     * Get patron's position in reservation queue.
     */
    public int getQueuePosition(String isbn, String patronId) {
        Queue<Reservation> queue = reservationQueues.get(isbn);
        if (queue == null) {
            return -1;
        }
        
        int position = 1;
        for (Reservation reservation : queue) {
            if (reservation.getPatronId().equals(patronId) && reservation.isActive()) {
                return position;
            }
            position++;
        }
        return -1;
    }
}