using System.Collections.Concurrent;

namespace OnlineStockBrokerageSystem
{
    public class Portfolio
    {
        private readonly Account _account;
        private readonly ConcurrentDictionary<string, int> _holdings;

        public Portfolio(Account account)
        {
            _account = account;
            _holdings = new ConcurrentDictionary<string, int>();
        }

        public void AddStock(Stock stock, int quantity)
        {
            _holdings.AddOrUpdate(stock.Symbol, quantity, (key, existingQty) => existingQty + quantity);
        }

        public void RemoveStock(Stock stock, int quantity)
        {
            if (_holdings.TryGetValue(stock.Symbol, out var currentQuantity))
            {
                if (currentQuantity > quantity)
                {
                    _holdings[stock.Symbol] = currentQuantity - quantity;
                }
                else if (currentQuantity == quantity)
                {
                    _holdings.TryRemove(stock.Symbol, out _);
                }
                else
                {
                    throw new InsufficientStockException("Insufficient stock quantity in the portfolio.");
                }
            }
            else
            {
                throw new InsufficientStockException("Stock not found in the portfolio.");
            }
        }

        public ConcurrentDictionary<string, int> GetHoldings() => _holdings;
    }
}