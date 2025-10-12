package restaurantmanagementsystem.model;

import restaurantmanagementsystem.enums.TableStatus;

public class Table {
    private final int id;
    private final int capacity;
    private TableStatus status;

    public Table(int id, int capacity) {
        this.id = id;
        this.capacity = capacity;
        this.status = TableStatus.AVAILABLE;
    }

    public int getId() { return id; }
    public int getCapacity() { return capacity; }
    public TableStatus getStatus() { return status; }
    public void setStatus(TableStatus status) { this.status = status; }
}