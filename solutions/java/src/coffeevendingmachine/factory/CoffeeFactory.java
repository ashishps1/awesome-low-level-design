package coffeevendingmachine.factory;

import coffeevendingmachine.enums.CoffeeType;
import coffeevendingmachine.templatemethod.Cappuccino;
import coffeevendingmachine.decorator.Coffee;
import coffeevendingmachine.templatemethod.Espresso;
import coffeevendingmachine.templatemethod.Latte;

public class CoffeeFactory {
    public static Coffee createCoffee(CoffeeType type) {
        switch (type) {
            case ESPRESSO:
                return new Espresso();
            case LATTE:
                return new Latte();
            case CAPPUCCINO:
                return new Cappuccino();
            default:
                throw new IllegalArgumentException("Unsupported coffee type: " + type);
        }
    }
}
