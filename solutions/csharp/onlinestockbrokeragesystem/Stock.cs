namespace OnlineStockBrokerageSystem
{
    public class Stock
    {
        public string Symbol { get; }
        public string Name { get; }
        public double Price { get; private set; }

        public Stock(string symbol, string name, double price)
        {
            Symbol = symbol;
            Name = name;
            Price = price;
        }

        public void UpdatePrice(double newPrice)
        {
            Price = newPrice;
        }
    }
}