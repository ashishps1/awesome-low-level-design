package coffeevendingmachine.decorator;

import coffeevendingmachine.enums.Ingredient;

import java.util.Map;

public abstract class CoffeeDecorator extends Coffee {
    protected Coffee decoratedCoffee;

    public CoffeeDecorator(Coffee coffee) {
        this.decoratedCoffee = coffee;
    }

    // Delegate calls to the wrapped object.
    // Concrete decorators will override these to add their own logic.
    @Override
    public int getPrice() {
        return decoratedCoffee.getPrice();
    }

    @Override
    public Map<Ingredient, Integer> getRecipe() {
        return decoratedCoffee.getRecipe();
    }

    @Override
    protected void addCondiments() {
        decoratedCoffee.addCondiments();
    }

    @Override
    public void prepare() {
        decoratedCoffee.prepare();
    }
}
