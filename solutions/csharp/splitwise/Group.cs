using System.Collections.Concurrent;
using System.Collections.Generic;

namespace Splitwise
{
    public class Group
    {
        public string Id { get; }
        public string Name { get; }
        public ConcurrentBag<User> Members { get; }
        public ConcurrentBag<Expense> Expenses { get; }

        public Group(string id, string name)
        {
            Id = id;
            Name = name;
            Members = new ConcurrentBag<User>();
            Expenses = new ConcurrentBag<Expense>();
        }

        public void AddMember(User user)
        {
            Members.Add(user);
        }

        public void AddExpense(Expense expense)
        {
            Expenses.Add(expense);
        }
    }
}