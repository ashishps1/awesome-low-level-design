class StockExchange
{
    private static volatile StockExchange instance;
    private static readonly object syncRoot = new object();
    private readonly Dictionary<string, List<Order>> buyOrders;
    private readonly Dictionary<string, List<Order>> sellOrders;
    private readonly object matchLock = new object();

    private StockExchange()
    {
        this.buyOrders = new Dictionary<string, List<Order>>();
        this.sellOrders = new Dictionary<string, List<Order>>();
    }

    public static StockExchange GetInstance()
    {
        if (instance == null)
        {
            lock (syncRoot)
            {
                if (instance == null)
                {
                    instance = new StockExchange();
                }
            }
        }
        return instance;
    }

    public void PlaceBuyOrder(Order order)
    {
        if (!buyOrders.ContainsKey(order.GetStock().GetSymbol()))
        {
            buyOrders[order.GetStock().GetSymbol()] = new List<Order>();
        }
        buyOrders[order.GetStock().GetSymbol()].Add(order);
        MatchOrders(order.GetStock());
    }

    public void PlaceSellOrder(Order order)
    {
        if (!sellOrders.ContainsKey(order.GetStock().GetSymbol()))
        {
            sellOrders[order.GetStock().GetSymbol()] = new List<Order>();
        }
        sellOrders[order.GetStock().GetSymbol()].Add(order);
        MatchOrders(order.GetStock());
    }

    private void MatchOrders(Stock stock)
    {
        lock (matchLock) // Critical section to prevent race conditions during matching
        {
            var buys = buyOrders.ContainsKey(stock.GetSymbol()) ? buyOrders[stock.GetSymbol()] : new List<Order>();
            var sells = sellOrders.ContainsKey(stock.GetSymbol()) ? sellOrders[stock.GetSymbol()] : new List<Order>();

            if (!buys.Any() || !sells.Any()) return;

            bool matchFound;
            do
            {
                matchFound = false;
                var bestBuy = FindBestBuy(buys);
                var bestSell = FindBestSell(sells);

                if (bestBuy != null && bestSell != null)
                {
                    double buyPrice = bestBuy.GetOrderType() == OrderType.MARKET ? stock.GetPrice() : bestBuy.GetPrice();
                    double sellPrice = bestSell.GetOrderType() == OrderType.MARKET ? stock.GetPrice() : bestSell.GetPrice();

                    if (buyPrice >= sellPrice)
                    {
                        ExecuteTrade(bestBuy, bestSell, sellPrice); // Trade at the seller's asking price
                        matchFound = true;
                    }
                }
            } while (matchFound);
        }
    }

    private void ExecuteTrade(Order buyOrder, Order sellOrder, double tradePrice)
    {
        Console.WriteLine($"--- Executing Trade for {buyOrder.GetStock().GetSymbol()} at ${tradePrice:F2} ---");

        var buyer = buyOrder.GetUser();
        var seller = sellOrder.GetUser();

        int tradeQuantity = Math.Min(buyOrder.GetQuantity(), sellOrder.GetQuantity());
        double totalCost = tradeQuantity * tradePrice;

        // Perform transaction
        buyer.GetAccount().Debit(totalCost);
        buyer.GetAccount().AddStock(buyOrder.GetStock().GetSymbol(), tradeQuantity);

        seller.GetAccount().Credit(totalCost);
        seller.GetAccount().RemoveStock(sellOrder.GetStock().GetSymbol(), tradeQuantity);

        // Update orders
        UpdateOrderStatus(buyOrder, tradeQuantity);
        UpdateOrderStatus(sellOrder, tradeQuantity);

        // Update stock's market price to last traded price
        buyOrder.GetStock().SetPrice(tradePrice);

        Console.WriteLine("--- Trade Complete ---");
    }

    private void UpdateOrderStatus(Order order, int quantityTraded)
    {
        // This is a simplified update logic. A real system would handle partial fills.
        order.SetStatus(OrderStatus.FILLED);
        order.SetState(new FilledState());
        string stockSymbol = order.GetStock().GetSymbol();
        
        // Remove from books
        if (buyOrders.ContainsKey(stockSymbol))
            buyOrders[stockSymbol].Remove(order);
        if (sellOrders.ContainsKey(stockSymbol))
            sellOrders[stockSymbol].Remove(order);
    }

    private Order FindBestBuy(List<Order> buys)
    {
        return buys
            .Where(o => o.GetStatus() == OrderStatus.OPEN)
            .OrderByDescending(o => o.GetPrice()) // Highest limit price is best
            .FirstOrDefault();
    }

    private Order FindBestSell(List<Order> sells)
    {
        return sells
            .Where(o => o.GetStatus() == OrderStatus.OPEN)
            .OrderBy(o => o.GetPrice()) // Lowest limit price is best
            .FirstOrDefault();
    }
}