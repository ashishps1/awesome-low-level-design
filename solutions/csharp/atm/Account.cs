namespace ATM
{
    public class Account
    {
        public string AccountNumber { get; }
        private double balance;

        public Account(string accountNumber, double balance)
        {
            AccountNumber = accountNumber;
            this.balance = balance;
        }

        public double Balance => balance;

        public void Debit(double amount)
        {
            balance -= amount;
        }

        public void Credit(double amount)
        {
            balance += amount;
        }
    }
}