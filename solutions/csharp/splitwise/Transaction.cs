namespace Splitwise
{
    public class Transaction
    {
        public string Id { get; }
        public User Sender { get; }
        public User Receiver { get; }
        public double Amount { get; }

        public Transaction(string id, User sender, User receiver, double amount)
        {
            Id = id;
            Sender = sender;
            Receiver = receiver;
            Amount = amount;
        }
    }
}