namespace OnlineStockBrokerageSystem
{
    public class Account
    {
        public string AccountId { get; }
        public User User { get; }
        private double _balance;
        public Portfolio Portfolio { get; }

        public Account(string accountId, User user, double initialBalance)
        {
            AccountId = accountId;
            User = user;
            _balance = initialBalance;
            Portfolio = new Portfolio(this);
        }

        public double GetBalance() => _balance;

        public void Deposit(double amount)
        {
            _balance += amount;
        }

        public void Withdraw(double amount)
        {
            if (_balance >= amount)
            {
                _balance -= amount;
            }
            else
            {
                throw new InsufficientFundsException("Insufficient funds in the account.");
            }
        }
    }
}