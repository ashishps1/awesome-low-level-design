package coffeevendingmachine;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Map;

public class CoffeeVendingMachineTest {

    private CoffeeVendingMachine machine;
    private final ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @BeforeEach
    void setUp() {
        machine = CoffeeVendingMachine.getInstance();
        System.setOut(new PrintStream(outputStream));

        // Reset and refill ingredients for each test
        machine.refillIngredient("Water", 150);
        machine.refillIngredient("Coffee", 100);
        machine.refillIngredient("Milk", 100);
    }

    @Test
    @DisplayName("Test coffee selection")
    void testSelectCoffee() {
        CoffeeRecipe espresso = machine.selectCoffee("Espresso");
        assertEquals("Espresso", espresso.getName());
        assertEquals(2.5, espresso.getPrice());
        assertEquals(50, espresso.getRecipe().get("Water"));
        assertEquals(20, espresso.getRecipe().get("Coffee"));
    }

    @Test
    @DisplayName("Test invalid coffee selection")
    void testInvalidCoffeeSelection() {
        Exception exception = assertThrows(RuntimeException.class, () -> {
            machine.selectCoffee("MochaCoffee");
        });

        String expectedMessage = "Invalid coffee recipe: MochaCoffee";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    @DisplayName("Test successful coffee dispensing")
    void testDispenseCoffee() {
        CoffeeRecipe latte = machine.selectCoffee("Latte");
        machine.dispenseCoffee(latte, new Payment(4.0));

        String output = outputStream.toString();
        assertTrue(output.contains("Dispensing: Latte"));
        assertTrue(output.contains("Processing Payment"));
        assertTrue(output.contains("Please collect your change: $1.0"));
    }

    @Test
    @DisplayName("Test insufficient payment")
    void testInsufficientPayment() {
        CoffeeRecipe cappuccino = machine.selectCoffee("Cappuccino");

        Exception exception = assertThrows(RuntimeException.class, () -> {
            machine.dispenseCoffee(cappuccino, new Payment(2.0));
        });

        String expectedMessage = "Insufficient payment for Cappuccino";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }



    @Test
    @DisplayName("Test ingredient consumption")
    void testIngredientConsumption() {
        CoffeeRecipe latte = machine.selectCoffee("Latte");

        // Check initial levels
        Map<String, Integer> beforeLevels = machine.showIngredientsMap();
        int initialWaterLevel = beforeLevels.get("Water");
        int initialCoffeeLevel = beforeLevels.get("Coffee");
        int initialMilkLevel = beforeLevels.get("Milk");

        machine.dispenseCoffee(latte, new Payment(3.0));

        // Check levels after dispensing
        Map<String, Integer> afterLevels = machine.showIngredientsMap();
        assertEquals(initialWaterLevel - 50, afterLevels.get("Water").intValue());
        assertEquals(initialCoffeeLevel - 20, afterLevels.get("Coffee").intValue());
        assertEquals(initialMilkLevel - 30, afterLevels.get("Milk").intValue());
    }

    @Test
    @DisplayName("Test ingredient refill")
    void testIngredientRefill() {
        // First check initial level
        Map<String, Integer> beforeLevels = machine.showIngredientsMap();
        int initialWaterLevel = beforeLevels.get("Water");

        // Add more water
        machine.refillIngredient("Water", 50);

        // Check after refill
        Map<String, Integer> afterLevels = machine.showIngredientsMap();
        assertEquals(initialWaterLevel + 50, afterLevels.get("Water").intValue());
    }
}
