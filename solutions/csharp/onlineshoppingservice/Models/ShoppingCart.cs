class ShoppingCart
{
    private readonly Dictionary<string, CartItem> items = new Dictionary<string, CartItem>();

    public void AddItem(Product product, int quantity)
    {
        if (items.ContainsKey(product.GetId()))
        {
            items[product.GetId()].IncrementQuantity(quantity);
        }
        else
        {
            items[product.GetId()] = new CartItem(product, quantity);
        }
    }

    public void RemoveItem(string productId)
    {
        items.Remove(productId);
    }

    public Dictionary<string, CartItem> GetItems()
    {
        return new Dictionary<string, CartItem>(items);
    }

    public double CalculateTotal()
    {
        return items.Values.Sum(item => item.GetPrice());
    }

    public void ClearCart()
    {
        items.Clear();
    }
}