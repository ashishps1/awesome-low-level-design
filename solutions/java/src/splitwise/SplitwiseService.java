package splitwise;

import splitwise.splitstrategy.SplitStrategy;
import splitwise.splitstrategy.SplitStrategyFactory;
import splitwise.splitstrategy.SplitType;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class SplitwiseService {
    private static SplitwiseService instance;
    private final Map<String, User> users;
    private final Map<String, Group> groups;
    private final Map<String, Expense> expenses;
    private final BalanceSheet balanceSheet;

    private SplitwiseService() {
        users = new ConcurrentHashMap<>();
        groups = new ConcurrentHashMap<>();
        expenses = new ConcurrentHashMap<>();
        balanceSheet = new BalanceSheet();
    }

    public static synchronized SplitwiseService getInstance() {
        if (instance == null) {
            instance = new SplitwiseService();
        }
        return instance;
    }

    public User createUser(String name, String email) {
        User user = new User(name, email);
        users.put(user.getUserId(), user);
        return user;
    }

    public Group createGroup(String name, List<String> userIds) {
        List<User> members = userIds.stream()
                .map(users::get)
                .collect(Collectors.toList());

        Group group = new Group(name, members);
        groups.put(group.getGroupId(), group);
        return group;
    }

    public Expense addExpense(String description, double amount, String paidByUserId, String groupId,
                           SplitType splitType, Map<String, Double> splitData) {
        User paidBy = users.get(paidByUserId);
        Group group = groupId == null ? null: groups.get(groupId);
        Map<User, Double> userSplitData = new HashMap<>();

        for (Map.Entry<String, Double> entry : splitData.entrySet()) {
            userSplitData.put(users.get(entry.getKey()), entry.getValue());
        }

        SplitStrategy strategy = SplitStrategyFactory.getStrategy(splitType);
        List<Split> splits = strategy.calculateSplits(userSplitData, amount);

        Expense expense = new Expense.Builder()
                .description(description)
                .amount(amount)
                .paidBy(paidBy)
                .group(group)
                .addSplits(splits)
                .build();

        expenses.put(expense.getExpenseId(), expense);
        balanceSheet.updateBalance(paidBy, splits);

        return expense;
    }

    public void settle(String fromUserId, String toUserId, double amount) {
        User fromUser = users.get(fromUserId);
        User toUser = users.get(toUserId);

        balanceSheet.settleBalance(fromUser, toUser, amount);
    }

    public void printBalances() {
        balanceSheet.printBalances();
    }

    public void printBalanceForUser(String userId) {
        balanceSheet.printBalanceForUser(users.get(userId));
    }

    public synchronized void deleteExpense(String expenseId) {
        Expense expense = expenses.remove(expenseId);
        if (expense != null) {
            // Reverse the balance updates
            List<Split> reverseSplits = expense.getSplits().stream()
                    .map(split -> new Split(split.getUser(), -split.getAmount()))
                    .collect(Collectors.toList());

            balanceSheet.updateBalance(expense.getPaidBy(), reverseSplits);
        }
    }
}