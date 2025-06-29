package splitwise.splitstrategy;

import splitwise.Split;
import splitwise.User;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ExactSplitStrategy implements SplitStrategy {
    @Override
    public List<Split> calculateSplits(Map<User, Double> splitData, double totalAmount) {
        double sum = splitData.values().stream().mapToDouble(Double::doubleValue).sum();

        if (Math.abs(sum - totalAmount) > 1e-6) {
            throw new IllegalArgumentException("Exact split amounts must sum up to total amount.");
        }

        List<Split> splits = new ArrayList<>();
        for (Map.Entry<User, Double> entry : splitData.entrySet()) {
            splits.add(new Split(entry.getKey(), entry.getValue()));
        }

        return splits;
    }
}
