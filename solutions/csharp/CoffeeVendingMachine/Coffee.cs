namespace CoffeeVendingMachine;

public class Coffee
{
    private readonly string _name;
    private readonly double _price;
    private readonly Dictionary<Ingredient, int> _recipe;

    public Coffee(string name, double price, Dictionary<Ingredient, int> recipe)
    {
        _name = name;
        _price = price;
        _recipe = recipe;
    }
    
    public string GetName() => _name;
    
    public double GetPrice() => _price;
    
    public Dictionary<Ingredient, int> GetRecipe() => _recipe;
}