class Stock
{
    private readonly string symbol;
    private double price;
    private readonly List<IStockObserver> observers = new List<IStockObserver>();

    public Stock(string symbol, double initialPrice)
    {
        this.symbol = symbol;
        this.price = initialPrice;
    }

    public string GetSymbol() { return symbol; }
    public double GetPrice() { return price; }

    public void SetPrice(double newPrice)
    {
        if (this.price != newPrice)
        {
            this.price = newPrice;
            NotifyObservers();
        }
    }

    public void AddObserver(IStockObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IStockObserver observer)
    {
        observers.Remove(observer);
    }

    private void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.Update(this);
        }
    }
}