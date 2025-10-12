class CaramelSyrupDecorator : CoffeeDecorator
{
    private const int COST = 30;
    private static readonly Dictionary<Ingredient, int> RECIPE_ADDITION = 
        new Dictionary<Ingredient, int> { { Ingredient.CARAMEL_SYRUP, 10 } };

    public CaramelSyrupDecorator(Coffee coffee) : base(coffee) { }

    public override string GetCoffeeType()
    {
        return decoratedCoffee.GetCoffeeType() + ", Caramel Syrup";
    }

    public override int GetPrice()
    {
        return decoratedCoffee.GetPrice() + COST;
    }

    public override Dictionary<Ingredient, int> GetRecipe()
    {
        var newRecipe = new Dictionary<Ingredient, int>(decoratedCoffee.GetRecipe());
        foreach (var pair in RECIPE_ADDITION)
        {
            if (newRecipe.ContainsKey(pair.Key))
                newRecipe[pair.Key] += pair.Value;
            else
                newRecipe[pair.Key] = pair.Value;
        }
        return newRecipe;
    }

    public override void Prepare()
    {
        base.Prepare();
        Console.WriteLine("- Drizzling Caramel Syrup on top.");
    }
}
