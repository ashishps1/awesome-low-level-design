package librarymanagementsystem.repositories;

import librarymanagementsystem.models.Patron;
import java.util.*;

/**
 * Repository for Patron entities.
 * Implements Repository pattern and DIP
 * Follows SRP - Only handles patron data access
 */
public class PatronRepository implements Repository<Patron, String> {
    private final Map<String, Patron> patrons;
    
    public PatronRepository() {
        this.patrons = new HashMap<>();
    }
    
    @Override
    public void save(Patron patron) {
        if (patron == null) {
            throw new IllegalArgumentException("Patron cannot be null");
        }
        patrons.put(patron.getPatronId(), patron);
    }
    
    @Override
    public Optional<Patron> findById(String patronId) {
        return Optional.ofNullable(patrons.get(patronId));
    }
    
    @Override
    public List<Patron> findAll() {
        return new ArrayList<>(patrons.values());
    }
    
    @Override
    public void delete(String patronId) {
        patrons.remove(patronId);
    }
    
    @Override
    public boolean exists(String patronId) {
        return patrons.containsKey(patronId);
    }
    
    // Custom query methods
    public Optional<Patron> findByEmail(String email) {
        return patrons.values().stream()
                .filter(patron -> email.equals(patron.getEmail()))
                .findFirst();
    }
    
    public List<Patron> findByName(String name) {
        return patrons.values().stream()
                .filter(patron -> patron.getName().toLowerCase().contains(name.toLowerCase()))
                .toList();
    }
}