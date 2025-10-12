class Espresso : Coffee
{
    public Espresso()
    {
        coffeeType = "Espresso";
    }

    public override void AddCondiments()
    {
        // No extra condiments for espresso
    }

    public override int GetPrice()
    {
        return 150;
    }

    public override Dictionary<Ingredient, int> GetRecipe()
    {
        return new Dictionary<Ingredient, int>
        {
            { Ingredient.COFFEE_BEANS, 7 },
            { Ingredient.WATER, 30 }
        };
    }
}