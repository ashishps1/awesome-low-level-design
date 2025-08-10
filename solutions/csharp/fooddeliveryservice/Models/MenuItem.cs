class MenuItem
{
    private readonly string id;
    private readonly string name;
    private readonly double price;
    private bool available;

    public MenuItem(string id, string name, double price)
    {
        this.id = id;
        this.name = name;
        this.price = price;
        this.available = true;
    }

    public string GetId() { return id; }
    public void SetAvailable(bool available) { this.available = available; }
    public string GetName() { return name; }
    public double GetPrice() { return price; }

    public string GetMenuItem()
    {
        return $"Name: {name}, Price: {price}";
    }
}