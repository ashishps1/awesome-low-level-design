class Account
{
    private readonly string username;
    private readonly string password;
    private readonly ShoppingCart cart;

    public Account(string username, string password)
    {
        this.username = username;
        this.password = password;
        this.cart = new ShoppingCart();
    }

    public ShoppingCart GetCart() { return cart; }
}