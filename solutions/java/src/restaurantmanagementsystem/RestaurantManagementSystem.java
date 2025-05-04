package restaurantmanagementsystem;

import restaurantmanagementsystem.payment.Payment;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class RestaurantManagementSystem {
    private static RestaurantManagementSystem instance;
    private final Map<String, MenuItem> menu;
    private final Map<String, Order> orders;
    private final List<Reservation> reservations;
    private final Map<Integer, Payment> payments;
    private final List<Staff> staff;
    private final Map<Integer, Table> tables;

    private RestaurantManagementSystem() {
        menu = new ConcurrentHashMap<>();
        orders = new ConcurrentHashMap<>();
        reservations = new CopyOnWriteArrayList<>();
        payments = new ConcurrentHashMap<>();
        staff = new CopyOnWriteArrayList<>();
        tables = new ConcurrentHashMap<>();
    }

    public static synchronized RestaurantManagementSystem getInstance() {
        if (instance == null) {
            instance = new RestaurantManagementSystem();
        }
        return instance;
    }

    public MenuItem addMenuItem(String name, double price) {
        MenuItem menuItem = new MenuItem(name, price);
        menu.put(name, new MenuItem(name, price));
        return menuItem;
    }

    public void removeMenuItem(String itemName) {
        menu.remove(itemName);
    }

    public List<MenuItem> getMenu() {
        return new ArrayList<>(menu.values());
    }

    public void addTable(int tableId, int capacity) {
        tables.put(tableId, new Table(tableId, capacity));
    }

    public Table reserveTable(int tableId) {
        Table table = tables.get(tableId);
        if (table == null) throw new IllegalArgumentException("Invalid table ID");
        table.reserve();
        return table;
    }

    public Order placeOrder(int tableId, List<OrderItem> items) {
        Table table = tables.get(tableId);
        if (table == null || table.isAvailable())
            throw new IllegalStateException("Table not reserved or invalid");

        Order order = new Order(table, items);
        orders.put(order.getId(), order);
        notifyKitchen(order);
        return order;
    }

    public void markOrderPreparing(String orderId) {
        Order order = orders.get(orderId);
        order.markPreparing();
        notifyKitchen(order);
    }

    public void markOrderReady(String orderId) {
        Order order = orders.get(orderId);
        order.markReady();
        notifyStaff(order);
    }

    public void markOrderServed(String orderId) {
        Order order = orders.get(orderId);
        order.markServed();
    }

    public Bill getBill(String orderId) {
        Order order = orders.get(orderId);

        if (order.getStatus() == OrderStatus.PAID)
            throw new IllegalStateException("Order already paid");

        order.markPaid();
        return new Bill(order.getId(), order.calculateTotal());
    }

    public void makePayment(Bill bill, Payment payment) {
        Order order = orders.get(bill.getOrderId());

        if (payment.processPayment(bill.getTotalAmount())) {
            bill.markPaymentCompleted();
            order.markPaid();
        } else {
            bill.markPaymentFailed();
            throw new RuntimeException("Payment failed for the orderId: " + order.getId());
        }
    }

    public Reservation makeReservation(String customerName, String contactNumber, int partySize, Timestamp reservationTime) {
        Reservation reservation = new Reservation(customerName, contactNumber, partySize, reservationTime);
        reservations.add(reservation);
        return reservation;
    }

    public void cancelReservation(Reservation reservation) {
        reservations.remove(reservation);
    }

    public void addStaff(Staff staff) {
        this.staff.add(staff);
    }

    public void removeStaff(Staff staff) {
        this.staff.remove(staff);
    }

    private void notifyKitchen(Order order) {
        // Notify kitchen staff to prepare the order
        // ...
    }

    private void notifyStaff(Order order) {
        // Notify relevant staff about the order status update
        // ...
    }
}
