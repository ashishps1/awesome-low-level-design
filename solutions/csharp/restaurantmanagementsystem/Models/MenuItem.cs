class MenuItem
{
    private readonly string id;
    private readonly string name;
    private readonly double price;

    public MenuItem(string id, string name, double price)
    {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public string GetId() => id;
    public string GetName() => name;
    public double GetPrice() => price;
}