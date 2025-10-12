package splitwise;


import splitwise.entities.Expense;
import splitwise.entities.Group;
import splitwise.entities.Transaction;
import splitwise.entities.User;
import splitwise.strategy.EqualSplitStrategy;
import splitwise.strategy.ExactSplitStrategy;
import splitwise.strategy.PercentageSplitStrategy;

import java.util.Arrays;
import java.util.List;

public class SplitwiseDemo {
    public static void main(String[] args) {
        // 1. Setup the service
        SplitwiseService service = SplitwiseService.getInstance();

        // 2. Create users and groups
        User alice = service.addUser("Alice", "alice@a.com");
        User bob = service.addUser( "Bob", "bob@b.com");
        User charlie = service.addUser("Charlie", "charlie@c.com");
        User david = service.addUser("David", "david@d.com");

        Group friendsGroup = service.addGroup("Friends Trip", List.of(alice, bob, charlie, david));

        System.out.println("--- System Setup Complete ---\n");

        // 3. Use Case 1: Equal Split
        System.out.println("--- Use Case 1: Equal Split ---");
        service.createExpense(new Expense.ExpenseBuilder()
                .setDescription("Dinner")
                .setAmount(1000)
                .setPaidBy(alice)
                .setParticipants(Arrays.asList(alice, bob, charlie, david))
                .setSplitStrategy(new EqualSplitStrategy())
        );

        service.showBalanceSheet(alice.getId());
        service.showBalanceSheet(bob.getId());
        System.out.println();

        // 4. Use Case 2: Exact Split
        System.out.println("--- Use Case 2: Exact Split ---");
        service.createExpense(new Expense.ExpenseBuilder()
                .setDescription("Movie Tickets")
                .setAmount(370)
                .setPaidBy(alice)
                .setParticipants(Arrays.asList(bob, charlie))
                .setSplitStrategy(new ExactSplitStrategy())
                .setSplitValues(Arrays.asList(120.0, 250.0))
        );

        service.showBalanceSheet(alice.getId());
        service.showBalanceSheet(bob.getId());
        System.out.println();

        // 5. Use Case 3: Percentage Split
        System.out.println("--- Use Case 3: Percentage Split ---");
        service.createExpense(new Expense.ExpenseBuilder()
                .setDescription("Groceries")
                .setAmount(500)
                .setPaidBy(david)
                .setParticipants(Arrays.asList(alice, bob, charlie))
                .setSplitStrategy(new PercentageSplitStrategy())
                .setSplitValues(Arrays.asList(40.0, 30.0, 30.0)) // 40%, 30%, 30%
        );

        System.out.println("--- Balances After All Expenses ---");
        service.showBalanceSheet(alice.getId());
        service.showBalanceSheet(bob.getId());

        service.showBalanceSheet(charlie.getId());
        service.showBalanceSheet(david.getId());

        System.out.println();

        // 6. Use Case 4: Simplify Group Debts
        System.out.println("--- Use Case 4: Simplify Group Debts for 'Friends Trip' ---");
        List<Transaction> simplifiedDebts = service.simplifyGroupDebts(friendsGroup.getId());
        if (simplifiedDebts.isEmpty()) {
            System.out.println("All debts are settled within the group!");
        } else {
            simplifiedDebts.forEach(System.out::println);
        }
        System.out.println();

        service.showBalanceSheet(bob.getId());

        // 7. Use Case 5: Partial Settlement
        System.out.println("--- Use Case 5: Partial Settlement ---");
        // From the simplified debts, we see Bob should pay Alice. Let's say Bob pays 100.
        service.settleUp(bob.getId(), alice.getId(), 100);

        System.out.println("--- Balances After Partial Settlement ---");
        service.showBalanceSheet(alice.getId());
        service.showBalanceSheet(bob.getId());
    }
}
