package librarymanagementsystem.repositories;

import java.util.List;
import java.util.Optional;

/**
 * Generic repository interface.
 * Follows DIP - High-level modules depend on this abstraction
 * Follows ISP - Minimal interface with only essential operations
 */
public interface Repository<T, ID> {
    void save(T entity);
    Optional<T> findById(ID id);
    List<T> findAll();
    void delete(ID id);
    boolean exists(ID id);
}