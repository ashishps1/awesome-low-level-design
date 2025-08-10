class Account
{
    private double balance;
    private readonly Dictionary<string, int> portfolio; // Stock symbol -> quantity
    private readonly object lockObj = new object();

    public Account(double initialCash)
    {
        this.balance = initialCash;
        this.portfolio = new Dictionary<string, int>();
    }

    public void Debit(double amount)
    {
        lock (lockObj)
        {
            if (balance < amount)
            {
                throw new InsufficientFundsException($"Insufficient funds to debit {amount}");
            }
            balance -= amount;
        }
    }

    public void Credit(double amount)
    {
        lock (lockObj)
        {
            balance += amount;
        }
    }

    public void AddStock(string symbol, int quantity)
    {
        lock (lockObj)
        {
            if (!portfolio.ContainsKey(symbol))
            {
                portfolio[symbol] = 0;
            }
            portfolio[symbol] += quantity;
        }
    }

    public void RemoveStock(string symbol, int quantity)
    {
        lock (lockObj)
        {
            int currentQuantity = portfolio.ContainsKey(symbol) ? portfolio[symbol] : 0;
            if (currentQuantity < quantity)
            {
                throw new InsufficientStockException($"Not enough {symbol} stock to sell.");
            }
            portfolio[symbol] = currentQuantity - quantity;
        }
    }

    public double GetBalance() { return balance; }
    public Dictionary<string, int> GetPortfolio() { return new Dictionary<string, int>(portfolio); }
    public int GetStockQuantity(string symbol) { return portfolio.ContainsKey(symbol) ? portfolio[symbol] : 0; }
}