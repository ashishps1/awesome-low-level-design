namespace ATM
{
    public class DepositTransaction : Transaction
    {
        public DepositTransaction(string transactionId, Account account, double amount)
            : base(transactionId, account, amount)
        {
        }

        public override void Execute()
        {
            account.Credit(amount);
        }
    }
}