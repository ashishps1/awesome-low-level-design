namespace ATM
{
    public abstract class Transaction
    {
        protected readonly string transactionId;
        protected readonly Account account;
        protected readonly double amount;

        protected Transaction(string transactionId, Account account, double amount)
        {
            this.transactionId = transactionId;
            this.account = account;
            this.amount = amount;
        }

        public abstract void Execute();
    }
}