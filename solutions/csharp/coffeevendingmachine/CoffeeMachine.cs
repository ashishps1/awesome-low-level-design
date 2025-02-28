using System;
using System.Collections.Generic;

namespace CoffeeVendingMachine
{
    public class CoffeeMachine
    {
        private static readonly CoffeeMachine instance = new CoffeeMachine();
        private readonly List<Coffee> coffeeMenu;
        private readonly Dictionary<string, Ingredient> ingredients;

        private CoffeeMachine()
        {
            coffeeMenu = new List<Coffee>();
            ingredients = new Dictionary<string, Ingredient>();
            InitializeIngredients();
            InitializeCoffeeMenu();
        }

        public static CoffeeMachine Instance
        {
            get { return instance; }
        }

        private void InitializeCoffeeMenu()
        {
            // Add coffee types to the menu
            var espressoRecipe = new Dictionary<Ingredient, int>
            {
                { ingredients["Coffee"], 1 },
                { ingredients["Water"], 1 }
            };
            coffeeMenu.Add(new Coffee("Espresso", 2.5, espressoRecipe));

            var cappuccinoRecipe = new Dictionary<Ingredient, int>
            {
                { ingredients["Coffee"], 1 },
                { ingredients["Water"], 1 },
                { ingredients["Milk"], 1 }
            };
            coffeeMenu.Add(new Coffee("Cappuccino", 3.5, cappuccinoRecipe));

            var latteRecipe = new Dictionary<Ingredient, int>
            {
                { ingredients["Coffee"], 1 },
                { ingredients["Water"], 1 },
                { ingredients["Milk"], 2 }
            };
            coffeeMenu.Add(new Coffee("Latte", 4.0, latteRecipe));
        }

        private void InitializeIngredients()
        {
            // Add ingredients to the inventory
            ingredients["Coffee"] = new Ingredient("Coffee", 10);
            ingredients["Water"] = new Ingredient("Water", 10);
            ingredients["Milk"] = new Ingredient("Milk", 10);
        }

        public void DisplayMenu()
        {
            Console.WriteLine("Coffee Menu:");
            foreach (var coffee in coffeeMenu)
            {
                Console.WriteLine($"{coffee.Name} - ${coffee.Price}");
            }
        }

        public Coffee SelectCoffee(string coffeeName)
        {
            foreach (var coffee in coffeeMenu)
            {
                if (string.Equals(coffee.Name, coffeeName, StringComparison.OrdinalIgnoreCase))
                {
                    return coffee;
                }
            }
            return null;
        }

        public void DispenseCoffee(Coffee coffee, Payment payment)
        {
            if (payment.Amount >= coffee.Price)
            {
                if (HasEnoughIngredients(coffee))
                {
                    UpdateIngredients(coffee);
                    Console.WriteLine($"Dispensing {coffee.Name}...");
                    double change = payment.Amount - coffee.Price;
                    if (change > 0)
                    {
                        Console.WriteLine($"Please collect your change: ${change}");
                    }
                }
                else
                {
                    Console.WriteLine($"Insufficient ingredients to make {coffee.Name}");
                }
            }
            else
            {
                Console.WriteLine($"Insufficient payment for {coffee.Name}");
            }
        }

        private bool HasEnoughIngredients(Coffee coffee)
        {
            foreach (var ingredient in coffee.Recipe)
            {
                if (ingredient.Key.Quantity < ingredient.Value)
                {
                    return false;
                }
            }
            return true;
        }

        private void UpdateIngredients(Coffee coffee)
        {
            foreach (var ingredient in coffee.Recipe)
            {
                ingredient.Key.UpdateQuantity(-ingredient.Value);
                if (ingredient.Key.Quantity < 3)
                {
                    Console.WriteLine($"Low inventory alert: {ingredient.Key.Name}");
                }
            }
        }
    }
}