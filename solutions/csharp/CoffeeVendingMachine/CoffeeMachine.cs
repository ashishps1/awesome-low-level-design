using System.Collections;

using System;
using System.Collections.Generic;

namespace CoffeeVendingMachine;

public class CoffeeMachine
{
    private static readonly CoffeeMachine _instance = new CoffeeMachine();
    private readonly List<Coffee> _coffeeMenu;
    private readonly Dictionary<string, Ingredient> _ingredients;

    private CoffeeMachine()
    {
        _coffeeMenu = new List<Coffee>();
        _ingredients = new Dictionary<string, Ingredient>();
        InitializeIngredients();
        InitializeCoffeeMenu();
    }

    public static CoffeeMachine GetInstance() => _instance;

    private void InitializeCoffeeMenu()
    {
        // Add coffee types to the menu
        var espressoRecipe = new Dictionary<Ingredient, int>
        {
            { _ingredients["Coffee"], 1 },
            { _ingredients["Water"], 1 }
        };
        _coffeeMenu.Add(new Coffee("Espresso", 2.5, espressoRecipe));

        var cappuccinoRecipe = new Dictionary<Ingredient, int>
        {
            { _ingredients["Coffee"], 1 },
            { _ingredients["Water"], 1 },
            { _ingredients["Milk"], 1 }
        };
        _coffeeMenu.Add(new Coffee("Cappuccino", 3.5, cappuccinoRecipe));

        var latteRecipe = new Dictionary<Ingredient, int>
        {
            { _ingredients["Coffee"], 1 },
            { _ingredients["Water"], 1 },
            { _ingredients["Milk"], 2 }
        };
        _coffeeMenu.Add(new Coffee("Latte", 4.0, latteRecipe));
    }

    private void InitializeIngredients()
    {
        // Add ingredients to the inventory
        _ingredients.Add("Coffee", new Ingredient("Coffee", 10));
        _ingredients.Add("Water", new Ingredient("Water", 10));
        _ingredients.Add("Milk", new Ingredient("Milk", 10));
    }

    public void DisplayMenu()
    {
        Console.WriteLine("Coffee Menu:");
        foreach (var coffee in _coffeeMenu)
        {
            Console.WriteLine($"{coffee.GetName()} - ${coffee.GetPrice()}");
        }
    }

    public Coffee SelectCoffee(string coffeeName)
    {
        lock (this)
        {
            foreach (var coffee in _coffeeMenu)
            {
                if (coffee.GetName().Equals(coffeeName, StringComparison.OrdinalIgnoreCase))
                {
                    return coffee;
                }
            }
            return null;
        }
    }

    public void DispenseCoffee(Coffee coffee, Payment payment)
    {
        lock (this)
        {
            if (payment.GetAmount() >= coffee.GetPrice())
            {
                if (HasEnoughIngredients(coffee))
                {
                    UpdateIngredients(coffee);
                    Console.WriteLine($"Dispensing {coffee.GetName()}...");
                    double change = payment.GetAmount() - coffee.GetPrice();
                    if (change >= 0)
                    {
                        Console.WriteLine($"Please collect your change: ${change}");
                    }
                }
                else
                {
                    Console.WriteLine($"Insufficient ingredients to make {coffee.GetName()}");
                }
            }
            else
            {
                Console.WriteLine($"Insufficient payment for {coffee.GetName()}");
            }
        }
    }

    private bool HasEnoughIngredients(Coffee coffee)
    {
        foreach (var entry in coffee.GetRecipe())
        {
            Ingredient ingredient = entry.Key;
            int requiredQuantity = entry.Value;
            if (ingredient.GetQuantity() < requiredQuantity)
            {
                return false;
            }
        }
        return true;
    }

    private void UpdateIngredients(Coffee coffee)
    {
        foreach (var entry in coffee.GetRecipe())
        {
            Ingredient ingredient = entry.Key;
            int requiredQuantity = entry.Value;
            ingredient.UpdateQuantity(-requiredQuantity);
            if (ingredient.GetQuantity() < 3)
            {
                Console.WriteLine($"Low inventory alert: {ingredient.GetName()}");
            }
        }
    }
}