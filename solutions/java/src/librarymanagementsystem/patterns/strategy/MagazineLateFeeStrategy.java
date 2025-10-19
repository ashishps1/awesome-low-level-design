package librarymanagementsystem.patterns.strategy;

/**
 * Concrete strategy for calculating magazine late fees.
 * Part of Strategy Design Pattern
 */
public class MagazineLateFeeStrategy implements LateFeeStrategy {
    private static final double DAILY_RATE = 0.25;
    
    @Override
    public double calculateFee(int daysLate) {
        if (daysLate <= 0) {
            return 0.0;
        }
        return daysLate * DAILY_RATE;
    }
    
    @Override
    public String getStrategyName() {
        return "Magazine Late Fee Strategy ($0.25/day)";
    }
}