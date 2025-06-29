package splitwise;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class BalanceSheet {
    // Map of balances: balances.get(A).get(B) means how much B owes A
    private final Map<User, Map<User, Double>> balances;

    public BalanceSheet() {
        this.balances = new ConcurrentHashMap<>();
    }

    public void updateBalance(User paidBy, List<Split> splits) {
        for (Split split : splits) {
            User owedBy = split.getUser();
            double amount = split.getAmount();

            if (owedBy.equals(paidBy)) continue;

            balances.computeIfAbsent(paidBy, k -> new HashMap<>());
            balances.computeIfAbsent(owedBy, k -> new HashMap<>());

            // Borrower owes lender
            balances.get(paidBy).put(owedBy,
                    balances.get(paidBy).getOrDefault(owedBy, 0.0) + amount);

            // Lender is owed by borrower (negative from borrower's view)
            balances.get(owedBy).put(paidBy,
                    balances.get(owedBy).getOrDefault(paidBy, 0.0) - amount);
        }
    }

    public void settleBalance(User payer, User payee, double amount) {
        balances.computeIfAbsent(payer, k -> new HashMap<>());
        balances.computeIfAbsent(payee, k -> new HashMap<>());

        double currentOwed = balances.get(payee).getOrDefault(payer, 0.0);

        if (currentOwed < amount) {
            throw new IllegalArgumentException("Trying to settle more than owed.");
        }

        balances.get(payee).put(payer, currentOwed - amount);
        balances.get(payer).put(payee, balances.get(payer).getOrDefault(payee, 0.0) + amount);

        // Optional cleanup: remove zero balances to keep the map clean
        if (Math.abs(balances.get(payee).get(payer)) < 1e-6) {
            balances.get(payee).remove(payer);
            balances.get(payer).remove(payee);
        }
    }

    public void printBalances() {
        for (User u1 : balances.keySet()) {
            for (User u2 : balances.get(u1).keySet()) {
                double amount = balances.get(u1).get(u2);
                if (amount > 0) {
                    System.out.printf("%s owes %s: %.2f%n", u2.getName(), u1.getName(), amount);
                }
            }
        }
    }

    public void printBalanceForUser(User user) {
        for (User user2 : balances.get(user).keySet()) {
            double amount = balances.get(user).get(user2);
            if (amount > 0) {
                System.out.printf("%s is owed %.2f by %s%n", user.getName(), amount, user2.getName());
            } else {
                System.out.printf("%s owes %s: %.2f%n", user.getName(), user2.getName(), -amount);
            }
        }
    }
}