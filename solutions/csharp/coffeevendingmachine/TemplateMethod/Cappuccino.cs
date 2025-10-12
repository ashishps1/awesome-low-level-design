class Cappuccino : Coffee
{
    public Cappuccino()
    {
        coffeeType = "Cappuccino";
    }

    public override void AddCondiments()
    {
        Console.WriteLine("- Adding steamed milk and foam.");
    }

    public override int GetPrice()
    {
        return 250;
    }

    public override Dictionary<Ingredient, int> GetRecipe()
    {
        return new Dictionary<Ingredient, int>
        {
            { Ingredient.COFFEE_BEANS, 7 },
            { Ingredient.WATER, 30 },
            { Ingredient.MILK, 100 }
        };
    }
}