package librarymanagementsystem.services;

import librarymanagementsystem.models.Patron;
import librarymanagementsystem.repositories.PatronRepository;
import librarymanagementsystem.exceptions.PatronNotFoundException;
import java.util.List;

/**
 * Service for patron management operations.
 * Follows SRP - Only handles patron-related business logic
 * Follows DIP - Depends on PatronRepository abstraction
 */
public class PatronService {
    private final PatronRepository patronRepository;
    
    public PatronService(PatronRepository patronRepository) {
        this.patronRepository = patronRepository;
    }
    
    public void registerPatron(Patron patron) {
        if (patronRepository.exists(patron.getPatronId())) {
            throw new IllegalArgumentException("Patron already exists: " + patron.getPatronId());
        }
        patronRepository.save(patron);
        System.out.println("✅ Patron registered: " + patron.getName());
    }
    
    public void updatePatron(Patron patron) {
        if (!patronRepository.exists(patron.getPatronId())) {
            throw new PatronNotFoundException("Patron not found: " + patron.getPatronId());
        }
        patronRepository.save(patron);
        System.out.println("✅ Patron updated: " + patron.getName());
    }
    
    public void removePatron(String patronId) {
        Patron patron = getPatron(patronId);
        
        // Business rule: Cannot remove patron with borrowed books
        if (patron.getCurrentBorrowedCount() > 0) {
            throw new IllegalStateException(
                "Cannot remove patron with borrowed books. Current borrowed: " + 
                patron.getCurrentBorrowedCount()
            );
        }
        
        patronRepository.delete(patronId);
        System.out.println("✅ Patron removed: " + patronId);
    }
    
    public Patron getPatron(String patronId) {
        return patronRepository.findById(patronId)
                .orElseThrow(() -> new PatronNotFoundException("Patron not found: " + patronId));
    }
    
    public List<Patron> getAllPatrons() {
        return patronRepository.findAll();
    }
    
    public List<Patron> searchPatronsByName(String name) {
        return patronRepository.findByName(name);
    }
    
    public Patron findPatronByEmail(String email) {
        return patronRepository.findByEmail(email)
                .orElseThrow(() -> new PatronNotFoundException("Patron not found with email: " + email));
    }
    
    public boolean canPatronBorrowMore(String patronId) {
        Patron patron = getPatron(patronId);
        return patron.canBorrowMoreBooks();
    }
}