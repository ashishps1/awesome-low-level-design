package splitwise.splitstrategy;

import splitwise.Split;
import splitwise.User;

import java.util.List;
import java.util.Map;

public interface SplitStrategy {
    List<Split> calculateSplits(Map<User, Double> splitData, double totalAmount);
}
