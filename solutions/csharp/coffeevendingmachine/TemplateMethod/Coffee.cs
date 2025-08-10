abstract class Coffee
{
    protected string coffeeType = "Unknown Coffee";

    public virtual string GetCoffeeType()
    {
        return coffeeType;
    }

    // The Template Method
    public virtual void Prepare()
    {
        Console.WriteLine($"\nPreparing your {GetCoffeeType()}...");
        GrindBeans();
        Brew();
        AddCondiments(); // The "hook" for base coffee types
        PourIntoCup();
        Console.WriteLine($"{GetCoffeeType()} is ready!");
    }

    // Common steps
    private void GrindBeans() { Console.WriteLine("- Grinding fresh coffee beans."); }
    private void Brew() { Console.WriteLine("- Brewing coffee with hot water."); }
    private void PourIntoCup() { Console.WriteLine("- Pouring into a cup."); }

    // Abstract step to be implemented by subclasses
    public abstract void AddCondiments();

    public abstract int GetPrice();
    public abstract Dictionary<Ingredient, int> GetRecipe();
}