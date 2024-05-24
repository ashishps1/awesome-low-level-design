package splitwise;

public class PercentSplit extends Split {
    private final double percent;

    public PercentSplit(User user, double percent) {
        super(user);
        this.percent = percent;
    }

    @Override
    public double getAmount() {
        return amount;
    }

    public double getPercent() {
        return percent;
    }
}
