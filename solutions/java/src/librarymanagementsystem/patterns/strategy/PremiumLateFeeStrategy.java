package librarymanagementsystem.patterns.strategy;

/**
 * Concrete strategy for premium members (no late fees).
 * Part of Strategy Design Pattern
 * Demonstrates flexibility of strategy pattern
 */
public class PremiumLateFeeStrategy implements LateFeeStrategy {
    
    @Override
    public double calculateFee(int daysLate) {
        return 0.0;  // Premium members don't pay late fees
    }
    
    @Override
    public String getStrategyName() {
        return "Premium Member Strategy (No Late Fees)";
    }
}