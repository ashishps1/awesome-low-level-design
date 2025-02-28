using System;
using System.Collections.Generic;

namespace Splitwise
{
    public class SplitwiseDemo
    {
        public static void Run()
        {
            var splitwiseService = SplitwiseService.GetInstance();

            // Create users
            var user1 = new User("1", "Alice", "alice@example.com");
            var user2 = new User("2", "Bob", "bob@example.com");
            var user3 = new User("3", "Charlie", "charlie@example.com");

            splitwiseService.AddUser(user1);
            splitwiseService.AddUser(user2);
            splitwiseService.AddUser(user3);

            // Create a group
            var group = new Group("1", "Apartment");
            group.AddMember(user1);
            group.AddMember(user2);
            group.AddMember(user3);

            splitwiseService.AddGroup(group);

            // Add an expense
            var expense = new Expense("1", 300.0, "Rent", user1);
            var equalSplit1 = new EqualSplit(user1);
            var equalSplit2 = new EqualSplit(user2);
            var percentSplit = new PercentSplit(user3, 20.0);

            expense.AddSplit(equalSplit1);
            expense.AddSplit(equalSplit2);
            expense.AddSplit(percentSplit);

            splitwiseService.AddExpense(group.Id, expense);

            // Settle balances
            splitwiseService.SettleBalance(user1.Id, user2.Id);
            splitwiseService.SettleBalance(user1.Id, user3.Id);

            // Print user balances
            foreach (var user in new[] { user1, user2, user3 })
            {
                Console.WriteLine($"User: {user.Name}");
                foreach (var entry in user.Balances)
                {
                    Console.WriteLine($"  Balance with {entry.Key}: {entry.Value}");
                }
            }
        }
    }
}