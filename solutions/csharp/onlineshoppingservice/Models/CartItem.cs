class CartItem
{
    private readonly Product product;
    private int quantity;

    public CartItem(Product product, int quantity)
    {
        this.product = product;
        this.quantity = quantity;
    }

    public Product GetProduct() { return product; }
    public int GetQuantity() { return quantity; }
    public void IncrementQuantity(int amount) { quantity += amount; }
    public double GetPrice() { return product.GetPrice() * quantity; }
}