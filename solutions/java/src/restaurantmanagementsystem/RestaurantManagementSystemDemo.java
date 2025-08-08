package restaurantmanagementsystem;

import restaurantmanagementsystem.decorator.Bill;
import restaurantmanagementsystem.model.*;

import java.util.List;

public class RestaurantManagementSystemDemo {
    public static void main(String[] args) {
        // --- 1. System Setup using the Restaurant Singleton ---
        System.out.println("=== Initializing Restaurant System ===");
        RestaurantManagementSystemFacade rmsFacade = RestaurantManagementSystemFacade.getInstance();

        // --- 2. Add table and staff ---
        Table table1 = rmsFacade.addTable(1, 4);
        Chef chef1 = rmsFacade.addChef("CHEF01", "Gordon");
        Waiter waiter1 = rmsFacade.addWaiter("W01", "Alice");

        // --- 3. Add menu items ---
        MenuItem pizza = rmsFacade.addMenuItem("PIZZA01", "Margherita Pizza", 12.50);
        MenuItem pasta = rmsFacade.addMenuItem("PASTA01", "Carbonara Pasta", 15.00);
        MenuItem coke = rmsFacade.addMenuItem("DRINK01", "Coke", 2.50);
        System.out.println("Initialization Complete.\n");

        // --- 4. Scenario: A waiter takes an order for a table ---
        // The Command Pattern is used inside the rmsFacade.takeOrder() method.
        System.out.println("=== SCENARIO 1: Taking an order ===");
        Order order1 = rmsFacade.takeOrder(table1.getId(), waiter1.getId(), List.of(pizza.getId(), coke.getId()));
        System.out.println("Order taken successfully. Order ID: " + order1.getOrderId());

        // --- 5. Scenario: Chef prepares food and notifies waiter ---
        System.out.println("\n=== SCENARIO 2: Chef prepares, Waiter gets notified ===");
        rmsFacade.markItemsAsReady(order1.getOrderId());
        rmsFacade.serveOrder(waiter1.getId(), order1.getOrderId());

        // --- 5. Scenario: Generate a bill with taxes and service charges ---
        // The Decorator Pattern is used inside rmsFacade.generateBill().
        System.out.println("\n=== SCENARIO 3: Generating the bill ===");
        Bill finalBill = rmsFacade.generateBill(order1.getOrderId());
        finalBill.printBill();
    }
}
