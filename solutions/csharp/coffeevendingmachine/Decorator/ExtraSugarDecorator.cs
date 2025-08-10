class ExtraSugarDecorator : CoffeeDecorator
{
    private const int COST = 10;
    private static readonly Dictionary<Ingredient, int> RECIPE_ADDITION = 
        new Dictionary<Ingredient, int> { { Ingredient.SUGAR, 1 } };

    public ExtraSugarDecorator(Coffee coffee) : base(coffee) { }

    public override string GetCoffeeType()
    {
        return decoratedCoffee.GetCoffeeType() + ", Extra Sugar";
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
        Console.WriteLine("- Stirring in Extra Sugar.");
    }
}