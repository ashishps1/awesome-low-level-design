package librarymanagementsystem.services;

import librarymanagementsystem.models.Book;
import librarymanagementsystem.models.Patron;
import librarymanagementsystem.models.LoanRecord;
import librarymanagementsystem.repositories.BookRepository;
import librarymanagementsystem.repositories.LoanRepository;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Service for book recommendations.
 * Follows SRP - Only handles recommendation logic
 * Supports optional extension: Recommendation System
 */
public class RecommendationService {
    private final BookRepository bookRepository;
    private final LoanRepository loanRepository;
    
    public RecommendationService(BookRepository bookRepository, LoanRepository loanRepository) {
        this.bookRepository = bookRepository;
        this.loanRepository = loanRepository;
    }
    
    /**
     * Recommend books based on patron's borrowing history.
     */
    public List<Book> recommendBooks(Patron patron, int limit) {
        // Get patron's borrowing history
        List<LoanRecord> history = loanRepository.findByPatronId(patron.getPatronId());
        
        if (history.isEmpty()) {
            // No history - return popular books
            return getPopularBooks(limit);
        }
        
        // Extract authors from borrowed books
        Set<String> favoriteAuthors = history.stream()
                .map(loan -> loan.getBook().getAuthor())
                .collect(Collectors.toSet());
        
        // Find books by same authors that patron hasn't borrowed
        Set<String> borrowedIsbns = history.stream()
                .map(loan -> loan.getBook().getIsbn())
                .collect(Collectors.toSet());
        
        List<Book> recommendations = bookRepository.findAll().stream()
                .filter(book -> !borrowedIsbns.contains(book.getIsbn()))
                .filter(book -> favoriteAuthors.contains(book.getAuthor()))
                .filter(Book::isAvailable)
                .limit(limit)
                .collect(Collectors.toList());
        
        // If not enough recommendations, add popular books
        if (recommendations.size() < limit) {
            List<Book> popular = getPopularBooks(limit - recommendations.size()).stream()
                    .filter(book -> !borrowedIsbns.contains(book.getIsbn()))
                    .toList();
            recommendations.addAll(popular);
        }
        
        return recommendations;
    }
    
    /**
     * Get most popular books (most borrowed).
     */
    public List<Book> getPopularBooks(int limit) {
        // Count loans per book
        Map<String, Long> loanCounts = loanRepository.findAll().stream()
                .collect(Collectors.groupingBy(
                        loan -> loan.getBook().getIsbn(),
                        Collectors.counting()
                ));
        
        // Sort by loan count and get top books
        return loanCounts.entrySet().stream()
                .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                .limit(limit)
                .map(entry -> bookRepository.findById(entry.getKey()))
                .filter(Optional::isPresent)
                .map(Optional::get)
                .filter(Book::isAvailable)
                .collect(Collectors.toList());
    }
    
    /**
     * Get similar books based on author.
     */
    public List<Book> getSimilarBooks(String isbn, int limit) {
        Book book = bookRepository.findById(isbn)
                .orElseThrow(() -> new IllegalArgumentException("Book not found: " + isbn));
        
        return bookRepository.findByAuthor(book.getAuthor()).stream()
                .filter(b -> !b.getIsbn().equals(isbn))
                .filter(Book::isAvailable)
                .limit(limit)
                .collect(Collectors.toList());
    }
}