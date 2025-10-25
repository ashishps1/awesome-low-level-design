package librarymanagementsystem.patterns.strategy;

/**
 * Concrete strategy for calculating book late fees.
 * Part of Strategy Design Pattern
 */
public class BookLateFeeStrategy implements LateFeeStrategy {
    private static final double DAILY_RATE = 0.50;
    
    @Override
    public double calculateFee(int daysLate) {
        if (daysLate <= 0) {
            return 0.0;
        }
        return daysLate * DAILY_RATE;
    }
    
    @Override
    public String getStrategyName() {
        return "Book Late Fee Strategy ($0.50/day)";
    }
}