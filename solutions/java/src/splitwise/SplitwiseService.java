package splitwise;

import splitwise.entities.*;

import java.util.*;
import java.util.stream.Collectors;

public class SplitwiseService {
    private static SplitwiseService instance;
    private final Map<String, User> users = new HashMap<>();
    private final Map<String, Group> groups = new HashMap<>();

    private SplitwiseService() {}

    public static synchronized SplitwiseService getInstance() {
        if (instance == null) {
            instance = new SplitwiseService();
        }
        return instance;
    }

    // --- Setup Methods ---
    public User addUser(String name, String email) {
        User user = new User(name, email);
        users.put(user.getId(), user);
        return user;
    }

    public Group addGroup(String name, List<User> members) {
        Group group = new Group(name, members);
        groups.put(group.getId(), group);
        return group;
    }

    public User getUser(String id) { return users.get(id); }
    public Group getGroup(String id) { return groups.get(id); }

    // --- Core Functional Methods (Facade) ---
    public synchronized void createExpense(Expense.ExpenseBuilder builder) {
        Expense expense = builder.build();
        User paidBy = expense.getPaidBy();

        for (Split split : expense.getSplits()) {
            User participant = split.getUser();
            double amount = split.getAmount();

            if (!paidBy.equals(participant)) {
                paidBy.getBalanceSheet().adjustBalance(participant, amount);
                participant.getBalanceSheet().adjustBalance(paidBy, -amount);
            }
        }
        System.out.println("Expense '" + expense.getDescription() + "' of amount " + expense.getAmount() + " created.");
    }

    public synchronized void settleUp(String payerId, String payeeId, double amount) {
        User payer = users.get(payerId);
        User payee = users.get(payeeId);
        System.out.println(payer.getName() + " is settling up " + amount + " with " + payee.getName());
        // Settlement is like a reverse expense. payer owes less to payee.

        payee.getBalanceSheet().adjustBalance(payer, -amount);
        payer.getBalanceSheet().adjustBalance(payee, amount);
    }

    public void showBalanceSheet(String userId) {
        User user = users.get(userId);
        user.getBalanceSheet().showBalances();
    }

    public List<Transaction> simplifyGroupDebts(String groupId) {
        Group group = groups.get(groupId);
        if (group == null) throw new IllegalArgumentException("Group not found");

        // Calculate net balance for each member within the group context
        Map<User, Double> netBalances = new HashMap<>();
        for (User member : group.getMembers()) {
            double balance = 0;
            for(Map.Entry<User, Double> entry : member.getBalanceSheet().getBalances().entrySet()) {
                // Consider only balances with other group members
                if (group.getMembers().contains(entry.getKey())) {
                    balance += entry.getValue();
                }
            }
            netBalances.put(member, balance);
        }

        // Separate into creditors and debtors
        List<Map.Entry<User, Double>> creditors = netBalances.entrySet().stream()
                .filter(e -> e.getValue() > 0).collect(Collectors.toList());
        List<Map.Entry<User, Double>> debtors = netBalances.entrySet().stream()
                .filter(e -> e.getValue() < 0).collect(Collectors.toList());

        creditors.sort(Map.Entry.comparingByValue(Comparator.reverseOrder()));
        debtors.sort(Map.Entry.comparingByValue());

        List<Transaction> transactions = new ArrayList<>();
        int i = 0, j = 0;
        while (i < creditors.size() && j < debtors.size()) {
            Map.Entry<User, Double> creditor = creditors.get(i);
            Map.Entry<User, Double> debtor = debtors.get(j);

            double amountToSettle = Math.min(creditor.getValue(), -debtor.getValue());
            transactions.add(new Transaction(debtor.getKey(), creditor.getKey(), amountToSettle));

            creditor.setValue(creditor.getValue() - amountToSettle);
            debtor.setValue(debtor.getValue() + amountToSettle);

            if (Math.abs(creditor.getValue()) < 0.01) i++;
            if (Math.abs(debtor.getValue()) < 0.01) j++;
        }
        return transactions;
    }
}