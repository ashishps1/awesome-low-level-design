package librarymanagementsystem.repositories;

import librarymanagementsystem.models.LoanRecord;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Repository for LoanRecord entities.
 * Implements Repository pattern and DIP
 * Follows SRP - Only handles loan data access
 */
public class LoanRepository implements Repository<LoanRecord, String> {
    private final Map<String, LoanRecord> loans;
    
    public LoanRepository() {
        this.loans = new HashMap<>();
    }
    
    @Override
    public void save(LoanRecord loan) {
        if (loan == null) {
            throw new IllegalArgumentException("Loan cannot be null");
        }
        loans.put(loan.getLoanId(), loan);
    }
    
    @Override
    public Optional<LoanRecord> findById(String loanId) {
        return Optional.ofNullable(loans.get(loanId));
    }
    
    @Override
    public List<LoanRecord> findAll() {
        return new ArrayList<>(loans.values());
    }
    
    @Override
    public void delete(String loanId) {
        loans.remove(loanId);
    }
    
    @Override
    public boolean exists(String loanId) {
        return loans.containsKey(loanId);
    }
    
    // Custom query methods
    public List<LoanRecord> findByPatronId(String patronId) {
        return loans.values().stream()
                .filter(loan -> loan.getPatron().getPatronId().equals(patronId))
                .collect(Collectors.toList());
    }
    
    public List<LoanRecord> findByIsbn(String isbn) {
        return loans.values().stream()
                .filter(loan -> loan.getBook().getIsbn().equals(isbn))
                .collect(Collectors.toList());
    }
    
    public List<LoanRecord> findActiveLoans() {
        return loans.values().stream()
                .filter(loan -> loan.getStatus() == LoanRecord.LoanStatus.ACTIVE)
                .collect(Collectors.toList());
    }
    
    public List<LoanRecord> findOverdueLoans() {
        return loans.values().stream()
                .filter(LoanRecord::isOverdue)
                .collect(Collectors.toList());
    }
}