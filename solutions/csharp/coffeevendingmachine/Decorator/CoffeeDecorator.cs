abstract class CoffeeDecorator : Coffee
{
    protected Coffee decoratedCoffee;

    public CoffeeDecorator(Coffee coffee)
    {
        decoratedCoffee = coffee;
    }

    public override int GetPrice()
    {
        return decoratedCoffee.GetPrice();
    }

    public override Dictionary<Ingredient, int> GetRecipe()
    {
        return decoratedCoffee.GetRecipe();
    }

    public override void AddCondiments()
    {
        decoratedCoffee.AddCondiments();
    }

    public override void Prepare()
    {
        decoratedCoffee.Prepare();
    }
}