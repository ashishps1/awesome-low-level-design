# Designing a Coffee Vending Machine

This blog post explores the object-oriented design and implementation of a Coffee Vending Machine using Java, a project that demonstrates managing coffee selections, inventory, and customer interactions.

## System Requirements

The Coffee Vending Machine is designed to:

1. **Offer Multiple Coffee Types:** Provide a selection of coffee types such as Espresso, Latte, and Cappuccino.
2. **Manage Inventory:** Track ingredients like coffee, milk, sugar, and water.
3. **Process Orders:** Handle customer coffee selections and dispense the correct beverage.
4. **Payment Handling:** Manage simplified payment transactions for the coffee.

## Core Use Cases

1. **Selecting a Coffee Type:** Customers choose their preferred type of coffee.
2. **Checking Ingredient Availability:** Ensure sufficient ingredients are available for the selected coffee.
3. **Dispensing Coffee:** Prepare and dispense the chosen coffee.
4. **Processing Payment:** Handle the transaction for the coffee purchase.

## UML/Class Diagrams

Key Classes Involved:

- `CoffeeVendingMachine`: Central class managing the vending machine.
- `Coffee`: Enum representing different types of coffee.
- `Ingredient`: Manages individual ingredients.
- `Inventory`: Tracks all available ingredients.
- `PaymentProcessor`: Handles payment transactions.

## Java Implementation

### Coffee Enum

Represents different coffee types available.

```java
public enum Coffee {
    ESPRESSO, LATTE, CAPPUCCINO
}
```
### Ingredient Class
```java
public class Ingredient {
    private String name;
    private int quantity;

    public Ingredient(String name, int quantity) {
        this.name = name;
        this.quantity = quantity;
    }

    public boolean useIngredient(int amount) {
        // Method implementation
    }

    // Getters and setters...
}
```
### Inventory Class
```java
import java.util.HashMap;
import java.util.Map;

public class Inventory {
    private Map<String, Ingredient> ingredients;

    public Inventory() {
        ingredients = new HashMap<>();
        // Initialize with default ingredients
    }

    public boolean checkIngredientAvailability(String ingredientName, int amount) {
        Ingredient ingredient = ingredients.get(ingredientName);
        return ingredient != null && ingredient.getQuantity() >= amount;
    }

    public void useIngredient(String ingredientName, int amount) {
        if (checkIngredientAvailability(ingredientName, amount)) {
            ingredients.get(ingredientName).useIngredient(amount);
        }
    }

    // Methods to add or update ingredients...
}
```
### CoffeeVendingMachine Class
```java
public class CoffeeVendingMachine {
    private Inventory inventory;
    private PaymentProcessor paymentProcessor;

    public CoffeeVendingMachine() {
        inventory = new Inventory();
        paymentProcessor = new PaymentProcessor();
    }

    public Coffee makeCoffee(Coffee coffeeType) {
        // Check if enough ingredients are available
        // If available, dispense the coffee
        // Handle payment
        return coffeeType; // Assuming coffee is dispensed
    }

    // Other necessary methods...
}
```
### PaymentProcessor Class
```java
public class PaymentProcessor {
    public boolean processPayment(double amount) {
        // Simulate payment processing
        return true; // Assuming payment is successful
    }
}
```