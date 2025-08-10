class Item
{
    private string code;
    private string name;
    private int price;

    public Item(string code, string name, int price)
    {
        this.code = code;
        this.name = name;
        this.price = price;
    }

    public string GetName()
    {
        return name;
    }

    public int GetPrice()
    {
        return price;
    }
}