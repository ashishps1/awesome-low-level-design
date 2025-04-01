using System.Collections.Generic;

namespace CoffeeVendingMachine
{
    public class Coffee
    {
        public string Name { get; }
        public double Price { get; }
        public Dictionary<Ingredient, int> Recipe { get; }

        public Coffee(string name, double price, Dictionary<Ingredient, int> recipe)
        {
            Name = name;
            Price = price;
            Recipe = recipe;
        }
    }
}