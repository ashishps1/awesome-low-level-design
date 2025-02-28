using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;

namespace OnlineStockBrokerageSystem
{
    public class StockBroker
    {
        private static StockBroker _instance;
        private readonly ConcurrentDictionary<string, Account> _accounts;
        private readonly ConcurrentDictionary<string, Stock> _stocks;
        private readonly Queue<Order> _orderQueue;
        private int _accountIdCounter;

        private StockBroker()
        {
            _accounts = new ConcurrentDictionary<string, Account>();
            _stocks = new ConcurrentDictionary<string, Stock>();
            _orderQueue = new Queue<Order>();
            _accountIdCounter = 1;
        }

        public static StockBroker GetInstance()
        {
            if (_instance == null)
            {
                _instance = new StockBroker();
            }
            return _instance;
        }

        public void CreateAccount(User user, double initialBalance)
        {
            var accountId = GenerateAccountId();
            var account = new Account(accountId, user, initialBalance);
            _accounts.TryAdd(accountId, account);
        }

        public Account GetAccount(string accountId)
        {
            _accounts.TryGetValue(accountId, out var account);
            return account;
        }

        public void AddStock(Stock stock)
        {
            _stocks.TryAdd(stock.Symbol, stock);
        }

        public Stock GetStock(string symbol)
        {
            _stocks.TryGetValue(symbol, out var stock);
            return stock;
        }

        public void PlaceOrder(Order order)
        {
            _orderQueue.Enqueue(order);
            ProcessOrders();
        }

        private void ProcessOrders()
        {
            while (_orderQueue.Count > 0)
            {
                var order = _orderQueue.Dequeue();
                try
                {
                    order.Execute();
                }
                catch (Exception e) when (e is InsufficientFundsException || e is InsufficientStockException)
                {
                    Console.WriteLine($"Order failed: {e.Message}");
                }
            }
        }

        private string GenerateAccountId()
        {
            return "A" + Interlocked.Increment(ref _accountIdCounter).ToString("D3");
        }
    }
}