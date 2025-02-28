using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;

namespace Splitwise
{
    public class SplitwiseService
    {
        private static SplitwiseService instance;
        private readonly ConcurrentDictionary<string, User> users;
        private readonly ConcurrentDictionary<string, Group> groups;

        // Replace AtomicInteger with a simple int
        private static int transactionCounter = 0;

        private static readonly string TRANSACTION_ID_PREFIX = "TXN";

        private SplitwiseService()
        {
            users = new ConcurrentDictionary<string, User>();
            groups = new ConcurrentDictionary<string, Group>();
        }

        public static SplitwiseService GetInstance()
        {
            if (instance == null)
            {
                instance = new SplitwiseService();
            }
            return instance;
        }

        public void AddUser(User user)
        {
            users.TryAdd(user.Id, user);
        }

        public void AddGroup(Group group)
        {
            groups.TryAdd(group.Id, group);
        }

        public void AddExpense(string groupId, Expense expense)
        {
            if (groups.TryGetValue(groupId, out var group))
            {
                group.AddExpense(expense);
                SplitExpense(expense);
                UpdateBalances(expense);
            }
        }

        private void SplitExpense(Expense expense)
        {
            double totalAmount = expense.Amount;
            var splits = expense.Splits;
            int totalSplits = splits.Count;

            double splitAmount = totalAmount / totalSplits;
            foreach (var split in splits)
            {
                if (split is EqualSplit)
                {
                    split.Amount = splitAmount;
                }
                else if (split is PercentSplit percentSplit)
                {
                    split.Amount = totalAmount * percentSplit.Percent / 100.0;
                }
            }
        }

        private void UpdateBalances(Expense expense)
        {
            foreach (var split in expense.Splits)
            {
                var paidBy = expense.PaidBy;
                var user = split.User;
                double amount = split.Amount;

                if (!paidBy.Equals(user))
                {
                    UpdateBalance(paidBy, user, amount);
                    UpdateBalance(user, paidBy, -amount);
                }
            }
        }

        private void UpdateBalance(User user1, User user2, double amount)
        {
            string key = GetBalanceKey(user1, user2);
            user1.Balances.AddOrUpdate(key, amount, (k, v) => v + amount);
        }

        private string GetBalanceKey(User user1, User user2)
        {
            return user1.Id + ":" + user2.Id;
        }

        public void SettleBalance(string userId1, string userId2)
        {
            if (users.TryGetValue(userId1, out var user1) && users.TryGetValue(userId2, out var user2))
            {
                string key = GetBalanceKey(user1, user2);
                double balance = user1.Balances.GetValueOrDefault(key, 0.0);

                if (balance > 0)
                {
                    CreateTransaction(user1, user2, balance);
                    user1.Balances[key] = 0.0;
                    user2.Balances[GetBalanceKey(user2, user1)] = 0.0;
                }
                else if (balance < 0)
                {
                    CreateTransaction(user2, user1, -balance);
                    user1.Balances[key] = 0.0;
                    user2.Balances[GetBalanceKey(user2, user1)] = 0.0;
                }
            }
        }

        private void CreateTransaction(User sender, User receiver, double amount)
        {
            string transactionId = GenerateTransactionId();
            var transaction = new Transaction(transactionId, sender, receiver, amount);
            // Process transaction (e.g., store it or notify users)
        }

        // Replace AtomicInteger logic with Interlocked.Increment
        private string GenerateTransactionId()
        {
            int transactionNumber = Interlocked.Increment(ref transactionCounter);
            return TRANSACTION_ID_PREFIX + transactionNumber.ToString("D6");
        }
    }
}