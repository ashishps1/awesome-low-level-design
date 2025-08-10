using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class SplitwiseDemo
{
    public static void Main(string[] args)
    {
        // 1. Setup the service
        SplitwiseService service = SplitwiseService.GetInstance();

        // 2. Create users and groups
        User alice = service.AddUser("Alice", "alice@a.com");
        User bob = service.AddUser("Bob", "bob@b.com");
        User charlie = service.AddUser("Charlie", "charlie@c.com");
        User david = service.AddUser("David", "david@d.com");

        Group friendsGroup = service.AddGroup("Friends Trip", new List<User> { alice, bob, charlie, david });

        Console.WriteLine("--- System Setup Complete ---\n");

        // 3. Use Case 1: Equal Split
        Console.WriteLine("--- Use Case 1: Equal Split ---");
        service.CreateExpense(new ExpenseBuilder()
                              .SetDescription("Dinner")
                              .SetAmount(1000)
                              .SetPaidBy(alice)
                              .SetParticipants(new List<User> { alice, bob, charlie, david })
                              .SetSplitStrategy(new EqualSplitStrategy()));

        service.ShowBalanceSheet(alice.GetId());
        service.ShowBalanceSheet(bob.GetId());
        Console.WriteLine();

        // 4. Use Case 2: Exact Split
        Console.WriteLine("--- Use Case 2: Exact Split ---");
        service.CreateExpense(new ExpenseBuilder()
                              .SetDescription("Movie Tickets")
                              .SetAmount(370)
                              .SetPaidBy(alice)
                              .SetParticipants(new List<User> { bob, charlie })
                              .SetSplitStrategy(new ExactSplitStrategy())
                              .SetSplitValues(new List<double> { 120.0, 250.0 }));

        service.ShowBalanceSheet(alice.GetId());
        service.ShowBalanceSheet(bob.GetId());
        Console.WriteLine();

        // 5. Use Case 3: Percentage Split
        Console.WriteLine("--- Use Case 3: Percentage Split ---");
        service.CreateExpense(new ExpenseBuilder()
                              .SetDescription("Groceries")
                              .SetAmount(500)
                              .SetPaidBy(david)
                              .SetParticipants(new List<User> { alice, bob, charlie })
                              .SetSplitStrategy(new PercentageSplitStrategy())
                              .SetSplitValues(new List<double> { 40.0, 30.0, 30.0 })); // 40%, 30%, 30%

        Console.WriteLine("--- Balances After All Expenses ---");
        service.ShowBalanceSheet(alice.GetId());
        service.ShowBalanceSheet(bob.GetId());
        service.ShowBalanceSheet(charlie.GetId());
        service.ShowBalanceSheet(david.GetId());
        Console.WriteLine();

        // 6. Use Case 4: Simplify Group Debts
        Console.WriteLine("--- Use Case 4: Simplify Group Debts for 'Friends Trip' ---");
        List<Transaction> simplifiedDebts = service.SimplifyGroupDebts(friendsGroup.GetId());
        if (simplifiedDebts.Count == 0)
        {
            Console.WriteLine("All debts are settled within the group!");
        }
        else
        {
            foreach (Transaction debt in simplifiedDebts)
            {
                Console.WriteLine(debt.ToString());
            }
        }
        Console.WriteLine();

        service.ShowBalanceSheet(bob.GetId());

        // 7. Use Case 5: Partial Settlement
        Console.WriteLine("--- Use Case 5: Partial Settlement ---");
        // From the simplified debts, we see Bob should pay Alice. Let's say Bob pays 100.
        service.SettleUp(bob.GetId(), alice.GetId(), 100);

        Console.WriteLine("--- Balances After Partial Settlement ---");
        service.ShowBalanceSheet(alice.GetId());
        service.ShowBalanceSheet(bob.GetId());
    }
}