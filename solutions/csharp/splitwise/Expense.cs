using System.Collections.Generic;

namespace Splitwise
{
    public class Expense
    {
        public string Id { get; }
        public double Amount { get; }
        public string Description { get; }
        public User PaidBy { get; }
        public List<Split> Splits { get; }

        public Expense(string id, double amount, string description, User paidBy)
        {
            Id = id;
            Amount = amount;
            Description = description;
            PaidBy = paidBy;
            Splits = new List<Split>();
        }

        public void AddSplit(Split split)
        {
            Splits.Add(split);
        }
    }
}