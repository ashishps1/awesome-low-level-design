class Inventory
{
    private readonly Dictionary<string, Item> itemMap = new Dictionary<string, Item>();
    private readonly Dictionary<string, int> stockMap = new Dictionary<string, int>();

    public void AddItem(string code, Item item, int quantity)
    {
        itemMap[code] = item;
        stockMap[code] = quantity;
    }

    public Item GetItem(string code)
    {
        return itemMap.GetValueOrDefault(code);
    }

    public bool IsAvailable(string code)
    {
        return stockMap.GetValueOrDefault(code, 0) > 0;
    }

    public void ReduceStock(string code)
    {
        if (stockMap.ContainsKey(code))
        {
            stockMap[code] = stockMap[code] - 1;
        }
    }
}