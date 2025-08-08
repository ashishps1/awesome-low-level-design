package restaurantmanagementsystem;

import restaurantmanagementsystem.command.Command;
import restaurantmanagementsystem.command.PrepareOrderCommand;
import restaurantmanagementsystem.command.ServeOrderCommand;
import restaurantmanagementsystem.decorator.*;
import restaurantmanagementsystem.model.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class RestaurantManagementSystemFacade {
    private static RestaurantManagementSystemFacade instance;
    private final Restaurant restaurant = Restaurant.getInstance();
    private final AtomicInteger orderIdCounter;
    private final Map<Integer, Order> orders;

    private RestaurantManagementSystemFacade() {
        this.orderIdCounter = new AtomicInteger(1);
        this.orders = new HashMap<>();
    }

    public static synchronized RestaurantManagementSystemFacade getInstance() {
        if (instance == null) {
            instance = new RestaurantManagementSystemFacade();
        }
        return instance;
    }

    public Table addTable(int id, int capacity) {
        Table table = new Table(id, capacity);
        restaurant.addTable(table);
        return table;
    }

    public Waiter addWaiter(String id, String name) {
        Waiter waiter = new Waiter(id, name);
        restaurant.addWaiter(waiter);
        return waiter;
    }

    public Chef addChef(String id, String name) {
        Chef chef = new Chef(id, name);
        restaurant.addChef(chef);
        return chef;
    }

    public MenuItem addMenuItem(String id, String name, double price) {
        MenuItem item = new MenuItem(id, name, price);
        restaurant.getMenu().addItem(item);
        return item;
    }

    public Order takeOrder(int tableId, String waiterId, List<String> menuItemIds) {
        Waiter waiter = restaurant.getWaiter(waiterId);
        if (waiter == null) {
            throw new IllegalArgumentException("Invalid waiter ID.");
        }
        // For simplicity, we get the first available chef.
        Chef chef = restaurant.getChefs().stream().findFirst()
                .orElseThrow(() -> new IllegalStateException("No chefs available."));

        Order order = new Order(orderIdCounter.getAndIncrement(), tableId);
        for (String itemId : menuItemIds) {
            MenuItem menuItem = restaurant.getMenu().getItem(itemId);
            OrderItem orderItem = new OrderItem(menuItem, order);
            // Waiter subscribes to each item to get notified when it's ready.
            orderItem.addObserver(waiter);
            order.addItem(orderItem);
        }

        // The Command pattern decouples the waiter (invoker) from the chef (receiver).
        Command prepareOrderCommand = new PrepareOrderCommand(order, chef);
        prepareOrderCommand.execute();

        orders.put(order.getOrderId(), order);

        return order;
    }

    public void markItemsAsReady(int orderId) {
        Order order = orders.get(orderId);
        System.out.println("\nChef has finished preparing order " + order.getOrderId());

        order.getOrderItems().forEach(item -> { // Preparing -> ReadyForPickup -> Notifies Observer (Waiter)
            item.nextState();
            item.nextState();
        });
    }

    public void serveOrder(String waiterId, int orderId) {
        Order order = orders.get(orderId);
        Waiter waiter = restaurant.getWaiter(waiterId);

        Command serveOrderCommand = new ServeOrderCommand(order, waiter);
        serveOrderCommand.execute();
    }

    public Bill generateBill(int orderId) {
        Order order = orders.get(orderId);
        // The Decorator pattern adds charges dynamically.
        BillComponent billComponent = new BaseBill(order);
        billComponent = new TaxDecorator(billComponent, 0.08); // 8% tax
        billComponent = new ServiceChargeDecorator(billComponent, 5.00); // $5 flat service charge

        return new Bill(billComponent);
    }
}
