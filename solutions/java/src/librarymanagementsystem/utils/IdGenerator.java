package librarymanagementsystem.utils;

import java.util.UUID;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Utility class for generating unique IDs.
 * Follows SRP - Only handles ID generation
 */
public class IdGenerator {
    private static final AtomicLong patronCounter = new AtomicLong(1000);
    private static final AtomicLong loanCounter = new AtomicLong(1);
    private static final AtomicLong branchCounter = new AtomicLong(1);
    
    /**
     * Generate a unique patron ID.
     */
    public static String generatePatronId() {
        return "P" + String.format("%06d", patronCounter.getAndIncrement());
    }
    
    /**
     * Generate a unique loan ID.
     */
    public static String generateLoanId() {
        return "L" + String.format("%08d", loanCounter.getAndIncrement());
    }
    
    /**
     * Generate a unique branch ID.
     */
    public static String generateBranchId() {
        return "BR" + String.format("%03d", branchCounter.getAndIncrement());
    }
    
    /**
     * Generate a UUID-based unique ID.
     */
    public static String generateUUID() {
        return UUID.randomUUID().toString();
    }
    
    /**
     * Generate a short unique ID (8 characters).
     */
    public static String generateShortId() {
        return UUID.randomUUID().toString().substring(0, 8);
    }
}       