class OrderLineItem
{
    private readonly string productId;
    private readonly string productName;
    private readonly int quantity;
    private readonly double priceAtPurchase;

    public OrderLineItem(string productId, string productName, int quantity, double priceAtPurchase)
    {
        this.productId = productId;
        this.productName = productName;
        this.quantity = quantity;
        this.priceAtPurchase = priceAtPurchase;
    }

    public string GetProductId() { return productId; }
    public int GetQuantity() { return quantity; }
}