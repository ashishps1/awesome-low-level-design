namespace ATM
{
    public class WithdrawalTransaction : Transaction
    {
        public WithdrawalTransaction(string transactionId, Account account, double amount)
            : base(transactionId, account, amount)
        {
        }

        public override void Execute()
        {
            account.Debit(amount);
        }
    }
}