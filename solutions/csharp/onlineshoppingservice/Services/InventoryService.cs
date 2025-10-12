class InventoryService
{
    private readonly Dictionary<string, int> stock = new Dictionary<string, int>();
    private readonly object lockObj = new object();

    public void AddStock(Product product, int quantity)
    {
        lock (lockObj)
        {
            if (!stock.ContainsKey(product.GetId()))
            {
                stock[product.GetId()] = 0;
            }
            stock[product.GetId()] += quantity;
        }
    }

    public void UpdateStockForOrder(List<OrderLineItem> items)
    {
        lock (lockObj)
        {
            // First, check if all items are in stock
            foreach (var item in items)
            {
                if (!stock.ContainsKey(item.GetProductId()) || stock[item.GetProductId()] < item.GetQuantity())
                {
                    throw new OutOfStockException($"Not enough stock for product ID: {item.GetProductId()}");
                }
            }

            // If all checks pass, deduct the stock
            foreach (var item in items)
            {
                stock[item.GetProductId()] -= item.GetQuantity();
            }
        }
    }
}