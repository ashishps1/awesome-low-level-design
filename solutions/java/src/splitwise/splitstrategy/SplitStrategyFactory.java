package splitwise.splitstrategy;

public class SplitStrategyFactory {
    public static SplitStrategy getStrategy(SplitType splitType) {
        return switch (splitType) {
            case EQUAL -> new EqualSplitStrategy();
            case EXACT -> new ExactSplitStrategy();
            case PERCENTAGE -> new PercentageSplitStrategy();
            default -> throw new IllegalArgumentException("Unsupported SplitType: " + splitType);
        };
    }
}
