class Account
{
    private readonly string accountNumber;
    private double balance;
    private readonly Dictionary<string, Card> cards;
    private readonly object accountLock = new object();

    public Account(string accountNumber, double balance)
    {
        this.accountNumber = accountNumber;
        this.balance = balance;
        this.cards = new Dictionary<string, Card>();
    }

    public string GetAccountNumber() => accountNumber;
    public double GetBalance() => balance;
    public Dictionary<string, Card> GetCards() => cards;

    public void Deposit(double amount)
    {
        lock (accountLock)
        {
            balance += amount;
        }
    }

    public bool Withdraw(double amount)
    {
        lock (accountLock)
        {
            if (balance >= amount)
            {
                balance -= amount;
                return true;
            }
            return false;
        }
    }
}