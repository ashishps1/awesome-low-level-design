package splitwise.strategy;

import splitwise.entities.Split;
import splitwise.entities.User;

import java.util.ArrayList;
import java.util.List;

public class ExactSplitStrategy implements SplitStrategy {
    @Override
    public List<Split> calculateSplits(double totalAmount, User paidBy, List<User> participants, List<Double> splitValues) {
        if (participants.size() != splitValues.size()) {
            throw new IllegalArgumentException("Number of participants and split values must match.");
        }
        if (Math.abs(splitValues.stream().mapToDouble(Double::doubleValue).sum() - totalAmount) > 0.01) {
            throw new IllegalArgumentException("Sum of exact amounts must equal the total expense amount.");
        }

        List<Split> splits = new ArrayList<>();
        for (int i = 0; i < participants.size(); i++) {
            splits.add(new Split(participants.get(i), splitValues.get(i)));
        }
        return splits;
    }
}
