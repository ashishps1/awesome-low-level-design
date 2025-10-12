class Latte : Coffee
{
    public Latte()
    {
        coffeeType = "Latte";
    }

    public override void AddCondiments()
    {
        Console.WriteLine("- Adding steamed milk.");
    }

    public override int GetPrice()
    {
        return 220;
    }

    public override Dictionary<Ingredient, int> GetRecipe()
    {
        return new Dictionary<Ingredient, int>
        {
            { Ingredient.COFFEE_BEANS, 7 },
            { Ingredient.WATER, 30 },
            { Ingredient.MILK, 150 }
        };
    }
}