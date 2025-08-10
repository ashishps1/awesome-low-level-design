class CoffeeFactory
{
    public static Coffee CreateCoffee(CoffeeType type)
    {
        switch (type)
        {
            case CoffeeType.ESPRESSO:
                return new Espresso();
            case CoffeeType.LATTE:
                return new Latte();
            case CoffeeType.CAPPUCCINO:
                return new Cappuccino();
            default:
                throw new ArgumentException($"Unsupported coffee type: {type}");
        }
    }
}