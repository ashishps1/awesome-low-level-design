package librarymanagementsystem.patterns.strategy;

/**
 * Strategy interface for calculating late fees.
 * Part of Strategy Design Pattern
 * Follows OCP - New strategies can be added without modifying existing code
 */
public interface LateFeeStrategy {
    double calculateFee(int daysLate);
    String getStrategyName();
}