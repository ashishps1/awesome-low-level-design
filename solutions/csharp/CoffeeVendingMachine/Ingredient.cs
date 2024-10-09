namespace CoffeeVendingMachine;

public class Ingredient
{
    private readonly string _name;
    private int _quantity;

    public Ingredient(string name, int quantity)
    {
        _name = name;
        _quantity = quantity;
    }
    
    public string GetName() => _name;
    
    public int GetQuantity() => _quantity;

    public void UpdateQuantity(int quantity)
    {
        lock (this)
        {
            _quantity += quantity;
        }
    }
}